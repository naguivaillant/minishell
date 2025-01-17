/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_spe_character.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:47:27 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/10 16:30:24 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	check_spesynthax_norm(char *str, int count)
{
	if (count > 0 && (str[count - 1]) == '&')
	{
		if (count != 2)
			return (false);
	}
	if (count > 0 && (str[count - 1]) == '|')
	{
		if (count != 1)
			return (false);
	}
	if (count > 0 && ((str[count - 1]) == '>' || (str[count - 1]) == '<'))
	{
		if (count > 2)
			return (false);
	}
	return (true);
}

bool	check_spe_synthax(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str && str[1] && ((*str == (*(str + 1)) \
	|| (i > 0 && *str == (*(str - 1))))))
	{
		count++;
		str++;
		i++;
	}
	if (check_spesynthax_norm(str, count) == false)
		return (false);
	return (true);
}

bool	correct_spe(char *rline)
{
	int	i;

	i = 0;
	while (rline && rline[i])
	{
		if (rline[i] == '\"')
		{
			i++;
			while (rline[i] && rline[i] != '\"')
				i++;
		}
		if (rline[i] == '\'')
		{
			i++;
			while (rline[i] && rline[i] != '\'')
				i++;
		}
		if (is_special_character(rline[i]))
		{
			if (!check_spe_synthax(&rline[i]))
				return (false);
		}
		i++;
	}
	return (true);
}

bool	check_spe_character(char *rline, int *i, char c)
{
	while (rline[++(*i)] && rline[*i] != c)
	{
		if (rline[*i] == ';' || rline[*i] == '\\')
			return (false);
	}
	return (true);
}

bool	check_spe_in_quote(char *rline, int i)
{
	if (rline[i] == '\'')
	{
		if (check_spe_character(rline, &i, '\'') == false)
			return (false);
	}
	if (rline[i] == '\"')
	{
		if (check_spe_character(rline, &i, '\"') == false)
			return (false);
	}
	return (true);
}
