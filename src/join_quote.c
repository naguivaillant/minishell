/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 22:41:15 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/11 22:41:37 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	find_quote(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}

void	iter_in_quote(char **str, int *i, int *j, char c)
{
	(*i)++;
	while ((*str)[*i] && (*str)[*i] != c)
	{
		(*str)[(*j)++] = (*str)[(*i)++];
	}
	if ((*str)[*i])
		(*i)++;
}

void	join_quote(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*str && (*str)[i])
	{
		if ((*str)[i] == '\'')
		{
			iter_in_quote(str, &i, &j, '\'');
		}
		else if ((*str)[i] == '\"')
		{
			iter_in_quote(str, &i, &j, '\"');
		}
		else
			(*str)[j++] = (*str)[i++];
	}
	(*str)[j] = '\0';
}
