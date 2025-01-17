/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str_synthax.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:30:08 by nassm             #+#    #+#             */
/*   Updated: 2023/10/12 07:21:18 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	check_redir_argsnorm(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			if (!is_heredocs(str, i) && !is_outappend(str, i))
				return (false);
			i++;
		}
		i++;
	}
	return (true);
}

bool	check_redir_args(char *str)
{
	int	i;
	int	count;
	int	redir;

	count = 0;
	redir = 0;
	if (check_redir_argsnorm(str) == false)
		return (false);
	i = 0;
	while (str[i])
	{
		if (!separator(str[i]) && str[i] != '<' && str[i] != '>'
			&& !is_special_character(str[i]))
			count++;
		if (str[i] == '<' || str[i] == '>')
			redir++;
		i++;
	}
	if (count != 0 || redir == 0)
		return (true);
	else
		return (false);
}

bool	check_synthax_str(char *rline)
{
	int	i;

	i = 0;
	while (rline[i] && separator(rline[i]))
		i++;
	if (rline[i] == '|')
		return (false);
	if (count_elem_char(rline, '(') != count_elem_char(rline, ')'))
		return (false);
	if (rline[0] == '|' || rline[0] == '&' || !has_matching_quotes(rline)
		|| !correct_spe(rline))
		return (false);
	if (!correct_spe(rline))
		return (false);
	if (!check_redir_args(rline))
		return (false);
	return (true);
}

bool	is_validinputnorm(char *rline, int i)
{
	if (check_spe_in_quote(rline, i) == false)
		return (false);
	if (rline[i] == '(')
		if (!is_correct_sub(rline, i - 1))
			return (false);
	if (rline[i] == ')')
		if (!bracket_open(rline, i))
			return (false);
	if (rline[i] == ';' || rline[i] == '\\')
		return (false);
	return (true);
}

bool	is_valid_input(char *rline)
{
	int	i;

	i = 0;
	if (!check_synthax_str(rline))
		return (false);
	while (rline[i])
	{
		if (is_validinputnorm(rline, i) == false)
			return (false);
		if (rline[i] == '|')
		{
			i++;
			while (rline[i] && separator(rline[i]))
				i++;
			if (i == (int)ft_strlen(rline))
				return (false);
			if (rline[i] == '|')
				return (false);
		}
		if (rline[i])
			i++;
	}
	return (true);
}
