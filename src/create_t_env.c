/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_t_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:34:08 by nagvaill          #+#    #+#             */
/*   Updated: 2023/10/12 01:26:43 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*create_new_env(char *str)
{
	t_env	*env;
	char	**tab;

	tab = ft_split(str, '=');
	if (!tab)
		return (0);
	env = malloc(sizeof(t_env));
	if (!env)
		return (0);
	env->next = NULL;
	env->key = ft_strdup(tab[0]);
	if (!env->key)
		return (0);
	env->value = ft_strdup(tab[1]);
	if (!env->value)
		return (0);
	ft_free_tab(tab);
	return (env);
}

t_env	*get_bottom_env(t_env *env)
{
	while (env && env->next != NULL)
		env = env->next;
	return (env);
}

void	add_env_back(t_env **env, t_env *new_env)
{
	t_env	*bottom;

	if (!new_env)
		return ;
	if (!env)
	{
		*env = new_env;
		return ;
	}
	bottom = get_bottom_env(*env);
	bottom->next = new_env;
}

t_env	*create_env_norm(int i, int nb, t_env *env, t_minishell *minishell)
{	
	while (i < nb)
	{
		if (i == 0)
		{
			env = create_new_env(minishell->env[i]);
			if (!env)
				return (NULL);
		}
		else
			add_env_back(&env, create_new_env(minishell->env[i]));
		i++;
	}
	return (env);
}

t_env	*create_env(t_minishell *minishell)
{
	t_env	*env;
	int		i;
	int		nb;

	nb = count_tab_line(minishell->env);
	env = NULL;
	i = 0;
	env = create_env_norm(i, nb, env, minishell);
	nb = count_tab_line(minishell->tmp);
	i = 0;
	while (i < nb)
	{
		add_env_back(&env, create_new_env(minishell->tmp[i]));
		i++;
	}
	return (env);
}
