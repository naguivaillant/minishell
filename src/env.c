/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:01:01 by mrabourd          #+#    #+#             */
/*   Updated: 2023/05/11 19:27:42 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_env_list(char **env, t_data *data)
{
	int		i;
	int		res;
	t_list	*new;

	i = 0;
	res = 0;
	new = NULL;
	if (env && (char *)&data->env->content == NULL)
	{
		while (env[i])
		{
			new = ft_lstnew(env[i]);
			res = ft_lstadd_back(&data->env, new);
			if (res == 1)
			{
				exit_all(data);
			}
			i++;
		}
	}
}

int	count_list(t_list *list)
{
	t_list	*tmp;
	int		i;

	tmp = list;
	i = 0;
	while (tmp->next != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	print_env(t_data *data)
{
	// int count = count_list(data->env);
	// printf("count %d\n", count);
	while (data->env)
	{
		if (data->env->full == 0)
			printf("%s\n", (char *)data->env->content);
		data->env = data->env->next;
	}
}
