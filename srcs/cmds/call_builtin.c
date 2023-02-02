/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:32:44 by brook             #+#    #+#             */
/*   Updated: 2023/02/02 18:55:43 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**lst_to_array(t_list *lst)
{
	int		i;
	int		size;
	char	**array;

	size = ft_lstsize(lst) + 1;
	array = malloc(sizeof(char *) * size);
	if (!array)
		return (NULL);
	i = 0;
	while (lst)
	{
		array[i++] = lst->content;
		lst = lst->next;
	}
	array[i] = NULL;
	return (array);
}

// int call_builtin(t_minishell *ms, t_cmd *cmd)
// {
// 	char **cmds;
// 	char **ori_cmds;

// 	cmds = lst_to_array(cmd->args);
// 	ori_cmds = cmds;
// 	if (ft_strcmp(*cmds, "cd") == 0)
// 		call_cd(ms, ++cmds);
// 	else if (ft_strcmp(*cmds, "env") == 0)
// 		call_env(ms);
// 	else if (ft_strcmp(*cmds, "export") == 0)
// 		call_export(ms, ++cmds);
// 	else if (ft_strcmp(*cmds, "exit") == 0)
// 		call_exit(ms, ++cmds);
// 	else if (ft_strcmp(*cmds, "unset") == 0)
// 		call_unset(ms, ++cmds);
// 	else if (ft_strcmp(*cmds, "pwd") == 0)
// 		call_pwd(ms);
// 	else if (ft_strcmp(*cmds, "echo") == 0)
// 		call_echo(ms, ++cmds);
// 	else
// 	{
// 		free(cmds);
// 		return (EXIT_FAILURE);
// 	}
// 	free(ori_cmds);
// 	return (EXIT_SUCCESS);
// }

void	builtin_caller(t_minishell *ms, char *cmd_name, char **args)
{
	args++;
	if (ft_strcmp(cmd_name, "cd") == 0)
		call_cd(ms, args);
	else if (ft_strcmp(cmd_name, "env") == 0)
		call_env(ms);
	else if (ft_strcmp(cmd_name, "export") == 0)
		call_export(ms, args);
	else if (ft_strcmp(cmd_name, "exit") == 0)
		call_exit(ms, args);
	else if (ft_strcmp(cmd_name, "unset") == 0)
		call_unset(ms, args);
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		call_pwd(ms);
	else if (ft_strcmp(cmd_name, "echo") == 0)
		call_echo(ms, args);
}

int	is_builtin(t_minishell *ms, char *cmd_name)
{
	char	**builtins;

	builtins = ms->builtins;
	while (*builtins != NULL)
	{
		if (ft_strcmp(*builtins, cmd_name) == 0)
			return (1);
		builtins++;
	}
	return (0);
}

int	call_builtin(t_minishell *ms, t_cmd *cmd)
{
	char	*cmd_name;
	char	**args;

	args = lst_to_array(cmd->args);
	cmd_name = cmd->cmd_name;
	if (is_builtin(ms, cmd_name) == 0)
	{
		free(args);
		return (EXIT_FAILURE);
	}
	builtin_caller(ms, cmd_name, args);
	free(args);
	return (EXIT_SUCCESS);
}
