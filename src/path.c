/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:05:25 by mrabourd          #+#    #+#             */
/*   Updated: 2023/06/19 17:01:37 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	print_path(t_data *data)
// {
// 	printf("path: %s\n", data->path.line);
// 	printf("tab0: %s\n", data->path.tab[0]);
// }

void	parse_path(t_data *data)/* a changer, checker dans data->env plutot */
{
	t_list	*tmp;

	tmp = data->env;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "PATH=", 5) == 0)
			data->path.line = ft_strdup(&tmp->content[5]);
		tmp = tmp->next;
	}
	if (data->env)
		data->path.tab = ft_split(data->path.line, ':');
	// print_path(data);
}
