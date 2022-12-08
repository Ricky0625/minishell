/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utilise.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:25:36 by chchin            #+#    #+#             */
/*   Updated: 2022/12/07 19:40:21 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*load_env_var(t_list *envp, char *var)
{
	t_env *env_var;

	while (envp != NULL)
	{
		env_var = envp->content;
		if (ft_strcmp(var, env_var->key) == 0)
			return (env_var);
		envp = envp->next;
	}
	return (NULL);
}

void edit_env_val(t_list *envp, char *var, char *value)
{
	t_env *env;

	env = load_env_var(envp, var);
	if (env)
		env->value = value;
	// else
		// add_env
}

char	*get_env_value(t_minishell *ms, char *key)
{
	t_list	*envp;
	t_env	*env_var;

	envp = ms->envp;
	while (envp != NULL)
	{
		env_var = envp->content;
		if (ft_strcmp(key, env_var->key) == 0)
			return (env_var->value);
		envp = envp->next;
	}
	return (NULL);
}