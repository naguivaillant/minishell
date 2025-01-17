/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str_synthax_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:05:40 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/12 07:21:23 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_elem_char(char *rline, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (rline[i])
	{
		if (rline[i] == '\'')
			while (rline[++i] && rline[i] != '\'')
				;
		if (rline[i] == '\"')
			while (rline[++i] && rline[i] != '\"')
				;
		if (rline[i] == c)
			count++;
		if (rline[i])
			i++;
	}
	return (count);
}

bool	is_correct_sub(char *rline, int i)
{
	while (i > 0 && rline[i] && ft_isspace(rline[i]))
		i--;
	if (i >= 0 && (rline[i] != '&' && rline[i] != '|'))
		return (false);
	return (true);
}

bool	bracket_open(char *rline, int i)
{
	while (i > 0 && rline[i] != '(')
		i--;
	if (i >= 0 && rline[i] != '(')
		return (false);
	return (true);
}

bool	is_heredocs(char *str, int i)
{
	int	j;
	int	count;

	j = i;
	count = 0;
	i++;
	while (str[i] == str[j])
	{
		i++;
		count++;
	}
	if (count > 2)
		return (false);
	while (str[i] && separator(str[i]))
		i++;
	if (i < (int)ft_strlen(str) && str[i] != '>' && str[i] != '<')
		return (true);
	return (false);
}

bool	is_outappend(char *str, int i)
{
	int	j;
	int	count;

	j = i;
	count = 0;
	i++;
	while (str[i] == str[j])
	{
		i++;
		count++;
	}
	while (str[i] && separator(str[i]))
		i++;
	if (i < (int)ft_strlen(str) && str[i] != '>' && str[i] != '<')
		return (true);
	return (false);
}
