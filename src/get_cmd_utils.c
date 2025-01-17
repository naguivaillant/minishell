/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 07:28:20 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/12 07:30:55 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	verif_cmd(char *cmd)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(cmd))
	{
		if (cmd[i] == '/' && cmd[i + 1] == '/')
			return (0);
		i++;
	}
	return (1);
}

char	*command_not_found(char *cmd)
{
	char	*str;

	if (cmd != NULL && ft_strlen(cmd) > 0)
	{
		str = ft_strjoin(cmd, ": Command not found");
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
		free(str);
		return ("127");
	}
	else if (cmd && ft_strchr(cmd, '/') != NULL)
	{
		str = ft_strjoin(cmd, ": No such file or directory \n");
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
		free(str);
		return ("1");
	}
	else
	{
		write(2, "Command not found \n", 19);
		return ("127");
	}
}
