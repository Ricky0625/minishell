/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:32:50 by chchin            #+#    #+#             */
/*   Updated: 2023/02/10 16:34:29 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_isdigit(char *args)
{
	int	i;

	i = 0;
	while (args[i])
		if (ft_isdigit(args[i++]) == 0)
			return (1);
	return (0);
}

void	call_exit(t_minishell *ms, char **args)
{
	write(1, "exit\n", 5);
	if (args != NULL && *args != NULL)
	{
		if (check_isdigit(*args))
		{
			ft_printf("exit: %s: numeric argument required\n", *args);
			exit(255);
		}
		if (ft_strarrsize(args) > 1)
		{
			show_error(TOO_MANY_ARG, "EXIT");
			return ;
		}
	}
	free(ms->prompt);
	ft_lstclear(&ms->envp, clear_env_var);
	exit(g_errno);
}
