/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagvaill <nagvaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:17:12 by nagvaill          #+#    #+#             */
/*   Updated: 2023/06/19 19:40:31 by nagvaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	while (data->path.tab[i])
	{
		tmp = ft_strjoin(data->path.tab[i], "/");
		new = ft_strjoin(tmp, cmd);
		if (access(new, F_OK | X_OK) != -1)
			return (new);
		free(new);
		i++;
	}
	return (NULL);
}