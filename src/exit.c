/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:33:03 by mrabourd          #+#    #+#             */
/*   Updated: 2023/05/11 19:01:52 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	exit_all(t_data *data)
{
	if (data->input)
		free (data->input);
	if (data->env && data->env != NULL)
		ft_lstclear(&data->env, free);
	if (data->cmd_list && data->cmd_list != NULL)
		ft_lstclear(&data->cmd_list, free);
	if (data->cmd && data->cmd != NULL)
		free_tab(data->cmd);
	exit(EXIT_FAILURE);
}
