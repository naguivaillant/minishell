/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:05:25 by mrabourd          #+#    #+#             */
/*   Updated: 2023/06/16 13:59:57 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parse_path(char **env, t_data *data)/* a changer, checker dans data->env plutot */
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			data->path.line = ft_strdup(&env[i][5]);
		i++;
	}
	if (env)
		data->path.tab = ft_split(data->path.line, ':');
}
