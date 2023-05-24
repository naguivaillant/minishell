/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:01:01 by mrabourd          #+#    #+#             */
/*   Updated: 2023/05/24 16:26:05 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
			if (ft_strchr(env[i], '=') == 0)
				new->full = 1;
			res = ft_lstadd_back(&data->env, new);
			if (res == 1)
				exit_all(data, 1);
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
	t_list	*tmp;

	tmp = data->env;
	// int count = count_list(data->env);
	// printf("count %d\n", count);
	while (tmp)
	{
		if (tmp->full == 0)
			printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}
