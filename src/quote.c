/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 23:53:27 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/11 23:54:09 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	nb_total_quote(char *str)
{
	int	i;
	int	nb_quote;

	i = 0;
	nb_quote = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			nb_quote++;
		i++;
	}
	return (nb_quote);
}

int	inside_dquote(char *str, int j, int *t)
{
	if (!str)
		return (j);
	(*t)++;
	while (str[*t] && str[*t] != '\"')
	{
		if (str[*t] == '\'')
			j++;
		(*t)++;
	}
	return (j);
}

int	inside_squote(char *str, int k, int *t)
{
	if (!str)
		return (k);
	(*t)++;
	while (str[*t] && str[*t] != '\'')
	{
		if (str[*t] == '\"')
			k++;
		(*t)++;
	}
	return (k);
}

bool	has_matching_quotes(char *str)
{
	int	j;
	int	k;
	int	t;
	int	count;

	j = 0;
	k = 0;
	t = 0;
	count = nb_total_quote(str);
	if (!find_quote(str))
		return (true);
	while (str[t] && t < (int)ft_strlen(str))
	{
		if (str[t] == '\"')
			j = inside_dquote(str, j, &t);
		if (str[t] == '\'')
			k = inside_squote(str, k, &t);
		if (str[t])
			t++;
	}
	count = count - k - j;
	if (count % 2 == 0)
		return (true);
	return (false);
}
