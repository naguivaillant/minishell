/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:01:01 by mrabourd          #+#    #+#             */
/*   Updated: 2023/06/19 17:04:16 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	put_env_in_tab(t_data *data)
{
	t_list	*tmp;
	int		len_env;
	int		i;

	i = 0;
	tmp = data->env;
	len_env = count_list(data->env);
	data->env_tab = malloc (sizeof(char *) * (len_env + 2));
	if (data->env_tab == NULL)
		exit_all(data, 1, "problem malloc env char**");
	while (tmp != NULL)
	{
		data->env_tab[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp->next;
	}
	data->env_tab[i] = NULL;
}

void	fill_env_list(char **env, t_data *data)
{
	int		i;
	int		res;
	t_list	*new;

	i = 0;
	res = 0;
	new = NULL;
	if (env)
	{
		while (env[i])
		{
			new = ft_lstnew(env[i]);
			if (ft_strchr(env[i], '=') == 0)
				new->full = 1;
			res = ft_lstadd_back(&data->env, new);
			if (res == 1)
				exit_all(data, 1, "There is a problem to fill the env list");
			i++;
		}
	}
	put_env_in_tab(data);
}

void	print_env(t_data *data)
{
	t_list	*tmp;

	tmp = data->env;
	// int count = count_list(data->env);
	// printf("count %d\n", count);
	printf("DEBUT ENV\n");
	while (tmp)
	{
		if (tmp->full == 0)
		{
			ft_putstr_fd(tmp->content, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
			// printf("%s\n", tmp->content);
		}
		tmp = tmp->next;
	}
	printf("FIN ENV\n");
}
