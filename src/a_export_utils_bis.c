/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_export_utils_bis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:02:04 by nassm             #+#    #+#             */
/*   Updated: 2023/10/10 15:31:31 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	contain_plusequal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && str[i - 1] == '+')
			return (true);
		i++;
	}
	return (false);
}

void	join_value(char ***env, char *temp, char *new)
{
	int		i;
	int		j;
	char	*todel;

	i = 0;
	j = 0;
	while (new[i] != '=')
		i++;
	i++;
	while ((*env)[j])
	{
		if (ft_strncmp(temp, (*env)[j], ft_strlen(temp)) == 0)
		{
			todel = (*env)[j];
			(*env)[j] = ft_strjoin((*env)[j], &new[i]);
			free(todel);
		}
		j++;
	}
}
