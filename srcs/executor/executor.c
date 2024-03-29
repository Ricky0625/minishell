/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:25:49 by brook             #+#    #+#             */
/*   Updated: 2023/02/10 12:22:14 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_child(t_minishell *ms, t_list *cur_proc, char **cmd, char **envp)
{
	t_cmd	*cur_cmd;
	t_cmd	*next_cmd;
	int		fd_out;

	cur_cmd = cur_proc->content;
	fd_out = dup(STDOUT_FILENO);
	if (cur_proc->next)
	{
		next_cmd = cur_proc->next->content;
		close(next_cmd->pipefd[0]);
		set_io(next_cmd->pipefd[1], STDOUT_FILENO);
	}
	if (cur_cmd->pipefd[0] != 0 && cur_cmd->infile == NULL)
		set_io(cur_cmd->pipefd[0], STDIN_FILENO);
	if (exec_redirt_in(ms, cur_cmd) == EXIT_FAILURE)
		exit(g_errno);
	exec_redirt_out(cur_cmd);
	signal_default();
	if (call_builtin(ms, cur_cmd) == 1 && cmd[0])
	{
		execve(cmd[0], cmd, envp);
		set_io(fd_out, STDOUT_FILENO);
		show_error(CMD_NOT_FOUND, *cmd);
	}
	exit(g_errno);
}

int	exec_pipe(t_minishell *ms, t_list *cur_proc, char **envp)
{
	t_cmd	*cur_cmd;
	t_cmd	*next_cmd;
	char	**cmd;

	cur_cmd = cur_proc->content;
	next_cmd = cur_proc->content;
	cmd = lst_to_array(cur_cmd->args);
	g_errno = 0;
	if (cur_proc->next)
	{
		next_cmd = cur_proc->next->content;
		pipe(next_cmd->pipefd);
	}
	cur_cmd->pid = fork();
	if (cur_cmd->pid == 0)
		exec_child(ms, cur_proc, cmd, envp);
	else
		free(cmd);
	return (EXIT_SUCCESS);
}

void	wait_pipe(t_minishell *ms)
{
	t_list	*cur_proc;
	t_cmd	*cur_cmd;
	int		status;

	cur_proc = ms->cmds;
	while (cur_proc)
	{
		cur_cmd = cur_proc->content;
		waitpid(cur_cmd->pid, &status, WUNTRACED);
		if (WIFEXITED(status))
			g_errno = (WEXITSTATUS(status));
		if (WIFSIGNALED(status))
			g_errno = INTERRUPTED;
		cur_proc = cur_proc->next;
	}
}

int	exe_one_cmd(t_minishell *ms, t_cmd *cur_cmd)
{
	int	fd_in;

	g_errno = 1;
	if (is_builtin(ms, cur_cmd->cmd_name) == 0)
		return (EXIT_FAILURE);
	fd_in = dup(STDOUT_FILENO);
	cur_cmd->pid = fork();
	if (cur_cmd->pid == 0)
		exit(exec_redirt_in(ms, cur_cmd));
	wait_pipe(ms);
	exec_redirt_out(cur_cmd);
	if (g_errno != 1 && g_errno != 130)
		call_builtin(ms, cur_cmd);
	set_io(fd_in, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

void	executor(t_minishell *ms)
{
	t_list	*cur_proc;
	t_cmd	*cur_cmd;
	t_cmd	*next_cmd;
	char	**envp;

	cur_proc = ms->cmds;
	while (cur_proc != NULL)
	{
		signal(SIGINT, SIG_IGN);
		cur_cmd = cur_proc->content;
		if (ms->cmds->next == NULL && exe_one_cmd(ms, cur_cmd) == 0)
			return ;
		envp = get_env_arry(ms);
		exec_pipe(ms, cur_proc, envp);
		if (cur_proc->next)
		{
			next_cmd = cur_proc->next->content;
			close(next_cmd->pipefd[1]);
		}
		if (cur_cmd->pipefd[0] != 0)
			close(cur_cmd->pipefd[0]);
		ft_freestrarr(envp);
		cur_proc = cur_proc->next;
	}
	wait_pipe(ms);
}
