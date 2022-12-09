/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:06:16 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/09 16:08:50 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_builtins(t_minishell *ms)
{
	char	**builtins;

	builtins = ft_calloc(BUILTINS_TOTAL + 1, sizeof(char *));
	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "env";
	builtins[4] = "unset";
	builtins[5] = "export";
	builtins[6] = "exit";
	ms->builtins = builtins;
}

void	init_minishell(t_minishell *ms, char **ev)
{
	ms->envp = NULL;
	init_environment(ms, ev);
	init_builtins(ms);
}
