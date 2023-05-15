/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:33:34 by mrabourd          #+#    #+#             */
/*   Updated: 2023/05/15 12:47:49 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_unset(t_data *data)
{
	t_list	*tmp;

	tmp = data->env;
	if (tmp && tmp->next != NULL)
	{
		if (ft_strncmp((char *)tmp->content, data->cmd_list->next->content, ft_strlen(data->cmd_list->next->content)) == 0)
		{
			printf("ok\n");
			data->env = tmp->next;
			ft_lstdelone(tmp, free);
		}
	}
	while (tmp->next->next != NULL)
	{
		if (tmp->next != NULL && ft_strncmp((char *)tmp->next->content, data->cmd_list->next->content, ft_strlen(data->cmd_list->next->content)) == 0)
		{
			ft_lstdelone(tmp->next, free);
			tmp->next = tmp->next->next;
		}
		tmp = tmp->next->next;
		// printf("tmp->content %s\n", (char *)tmp->content);
		// printf("data->cmd_list->next->content %s\n", (char *)data->cmd_list->next->content);
	}
}