/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagvaill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:17:12 by nagvaill          #+#    #+#             */
/*   Updated: 2023/06/16 13:17:14 by nagvaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**get_cmd_path(t_data *data)
{
	int	i;

	i = 0;
	while (data->env && data->env[i])
	{
		if (!strncmp(data->env[i], "PATH=", 5))
		{
			return (ft_split(data->env[i] + 5, ':'));
		}
		i++;
	}
	return (NULL);
}

char	*cmd_final_state(t_data *data, char *cmd)
{
	char	*new;
	char	*tmp;
	int		i;

	i = 0;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) != -1)
			return (cmd);
	}
	data->path = get_cmd_path(data);
	if (!data->path)
		return (NULL);
	while (data->path[i])
	{
		tmp = ft_strjoin(data->path[i], "/");
		new = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(new, F_OK | X_OK) != -1)
			return (new);
		free(new);
		i++;
	}
	return (NULL);
}
