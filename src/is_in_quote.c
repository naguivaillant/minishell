/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_in_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 22:40:32 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/11 22:40:54 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_in_squote(char *cmd, int i)
{
	int	count;
	int	pos;

	pos = 0;
	count = 0;
	while (cmd[pos] && pos < i)
	{
		if (cmd[pos] == '\'' && !is_in_dquote(cmd, pos))
		{
			count++;
			pos++;
			while (cmd[pos] && cmd[pos] != '\'' && pos < i)
				pos++;
			if (cmd[pos] == '\'')
				count++;
		}
		pos++;
	}
	if (count % 2 != 0)
		return (true);
	return (false);
}

bool	is_in_dquote(char *cmd, int i)
{
	int	pos;
	int	count;

	pos = 0;
	count = 0;
	while (cmd[pos] && pos < i)
	{
		if (cmd[pos] == '\"' && !is_in_squote(cmd, pos))
		{
			count++;
			pos++;
			while (cmd[pos] && cmd[pos] != '\"' && pos < i)
				pos++;
			if (cmd[pos] == '\"')
				count++;
		}
		pos++;
	}
	if (count % 2 != 0)
		return (true);
	return (false);
}
