/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 10:57:46 by chchin            #+#    #+#             */
/*   Updated: 2023/02/10 12:19:57 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief List all the environment variable
 *
 * Iterate through the environment variables, if the value is not just a '\0',
 * print the environemnt variable along with its value in a format of:
 * 		`key=value`
*/
void	call_env(t_minishell *ms, char **args)
{
	t_list	*envp;
	t_env	*env_var;

	if (args != NULL && *args != NULL)
	{
		show_error(FILE_NOT_FOUND, *args);
		return ;
	}
	envp = ms->envp;
	while (envp != NULL)
	{
		env_var = envp->content;
		if (env_var->value != NULL)
		{
			if (env_var->value[0] != '\0')
				ft_printf("%s=%s\n", env_var->key, env_var->value);
			else if (env_var->value[0] == '\0')
				ft_printf("%s=\n", env_var->key);
		}
		envp = envp->next;
	}
}
