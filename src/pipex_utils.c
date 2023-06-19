/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:17:12 by nagvaill          #+#    #+#             */
/*   Updated: 2023/06/19 16:56:48 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	**get_cmd_path(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (data->env && data->env[i])
// 	{
// 		if (!strncmp(data->env[i], "PATH=", 5))
// 		{
// 			return (ft_split(data->env[i] + 5, ':'));
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

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
	// if (!data->path)
	// 	return (NULL);
	while (data->path.tab[i])
	{
		fprintf(stderr, "path: %s\n", data->path.tab[i]);
		tmp = ft_strjoin(data->path.tab[i], "/");
		fprintf(stderr, "tmp: %s\n", tmp);
		new = ft_strjoin(tmp, cmd);
		// free(tmp);
		if (access(new, F_OK | X_OK) != -1)
			return (new);
		free(new);
		i++;
	}
	return (NULL);
}