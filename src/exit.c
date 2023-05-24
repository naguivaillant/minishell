/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:33:03 by mrabourd          #+#    #+#             */
/*   Updated: 2023/05/24 16:25:49 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free (tab[i]);
		i++;
	}
	free (tab);
}

void	exit_all(t_data *data, int err)
{
	// if (data->env && data->env != NULL)
	// {
	// 	ft_lstclear(&data->env, free);
	// }
	if (data->token_list && data->token_list != NULL)
		ft_lstclear(&data->token_list, del);
	if (data->cmd && data->cmd != NULL)
		free_tab(data->cmd);
	if (data->path.tab && data->path.tab != NULL)
		free_tab(data->path.tab);
	if (data->path.line && data->path.line != NULL)
		free (data->path.line);
	if (err == 1)
	{
		exit(EXIT_FAILURE);
		printf("ERROR\n");
	}
	exit(EXIT_SUCCESS);
}
