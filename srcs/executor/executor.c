/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:25:49 by brook             #+#    #+#             */
/*   Updated: 2023/01/10 19:14:50 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_io(int rfd, int wfd)
{
	if (rfd != STDIN_FILENO)
	{
		dup2(rfd, STDIN_FILENO);
		close(rfd);
	}
	if (wfd != STDOUT_FILENO)
	{
		dup2(wfd, STDOUT_FILENO);
		close(wfd);
	}
}

void	exec_child(t_minishell *ms, int *fd, char **cmd, char **envp)
{
	int		ret;

	ret = EXIT_SUCCESS;
	set_io(STDIN_FILENO, fd[1]);
	if (call_buildin(ms, cmd) == 1)
		ret = execve(cmd[0], cmd, envp);
	exit(ret);
}

int	exec_pipe(t_minishell *ms, t_list *cmds, char **cmd, char **envp)
{
	int		ret;
	pid_t	pid;
	int		status;
	int		pipefd[2];

	ret = EXIT_SUCCESS;
	if (cmds->next != NULL)
		pipe(pipefd);
	pid = fork();
	if (pid == 0)
		exec_child(ms, pipefd, cmd, envp);
	waitpid(pid, &status, 0);
	if (pipefd[1] == 1)
		close(pipefd[1]);
	if (pipefd[0] != 0)
		close(pipefd[0]);
	return (ret);
}

int	executor(t_minishell *ms)
{
	t_list	*cmds;
	t_cmd	*cmd;
	char	**cmd_args;
	char	**envp;

	cmds = ms->cmds;
	while (cmds != NULL)
	{
		cmd = cmds->content;
		cmd_args = lst_to_array(cmd->args);
		if (cmd_args[0])
		{
			if (cmds->next == NULL && call_buildin(ms, cmd_args) == 1)
			{
				envp = get_env_arry(ms);
				exec_pipe(ms, cmds, cmd_args, envp);
				free(envp);
			}
		}
		cmds = cmds->next;
		free(cmd_args);
	}
	return (0);
}
