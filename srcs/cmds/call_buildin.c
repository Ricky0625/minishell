/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_buildin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:32:44 by brook             #+#    #+#             */
/*   Updated: 2023/02/02 11:17:15 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	call_buildin(t_minishell *ms, t_cmd *cmd)
{
	char	**cmds;

	// show_cmd_block(cmd);
	cmds = lst_to_array(cmd->args);
	if (ft_strcmp(*cmds, "cd") == 0)
		call_cd(ms, ++cmds);
	else if (ft_strcmp(*cmds, "env") == 0)
		call_env(ms);
	else if (ft_strcmp(*cmds, "export") == 0)
		call_export(ms, ++cmds);
	else if (ft_strcmp(*cmds, "exit") == 0)
		call_exit(ms, ++cmds);
	else if (ft_strcmp(*cmds, "unset") == 0)
		call_unset(ms, ++cmds);
	else if (ft_strcmp(*cmds, "pwd") == 0)
		call_pwd(ms);
	else if (ft_strcmp(*cmds, "echo") == 0)
		call_echo(ms, ++cmds);
	else
	{
		free(cmds);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
