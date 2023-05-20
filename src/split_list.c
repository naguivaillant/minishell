/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:53:43 by mrabourd          #+#    #+#             */
/*   Updated: 2023/05/20 16:27:39 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	split_meta(t_data *data, char *str, int *i, int *j)
{
	(*i)++;
	if (str[*i] && str[*i] == str[*j])
	{
		(*i)++;/* probleme si on termine par un double meta */
		add_node(data, str, *i, *j);
		while (str[*i] && is_space(str[*i]) == 1)
			(*i)++;
		if (str[*i])
			*j = *i;
		else
			return ;
	}
	else
		add_node(data, str, *i, *j);
	while (str[*i] && is_space(str[*i]) == 1)
		(*i)++;
	*j = *i;
	(*i)--;
}

static void	split_quotes(t_data *data, char *str, int *i, int *j)
{
	(*i)++;
	if (str[*i])
		*j = *i;
	else
		return ;
	while (str[*i] != '\"')
	{
		(*i)++;
	}
	if (str[*i] == '\"')
	{
		add_node(data, str, *i, *j);
		if (str[*i])
		{
			(*i)++;
			*j = *i;
			(*i)--;
		}
		else
			return ;
	}
}

/* A NORMER */
void	split_in_list(t_data *data, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = ft_strtrim(str, " ");
	while (str[i])
	{	
		if (j != i && (is_metacharacter(str[i]) == 1 || is_space(str[i]) == 1 || str[i] == '\"'))
		{
			add_node(data, str, i, j);
			while (str[i] && is_space(str[i]) == 1)
				i++;
			j = i;
		}
		if (str[i] && j == i && is_space(str[i]) == 1)
		{
			while (str[i] && is_space(str[i]) == 1)
				i++;
			j = i;
		}
		if (str[i] && i == j && is_metacharacter(str[i]) == 1)
			split_meta(data, str, &i, &j);
		if (str[i] && i == j && str[i] == '\"')
			split_quotes(data, str, &i, &j);
		i++;
	}
	if (j != i && is_space(str[j]) == 0)
		add_node(data, str, i, j);
	free (str);
}

/* CA MARCHE mais va falloir normer  :// */
/*
void	split_in_list(t_data *data, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = ft_strtrim(str, " ");
	while (str[i])
	{	
		if (j != i && (is_metacharacter(str[i]) == 1 || is_space(str[i]) == 1 || str[i] == '\"'))
		{
			add_node(data, str, i, j);
			while (str[i] && is_space(str[i]) == 1)
				i++;
			j = i;
		}
		if (str[i] && j == i && is_space(str[i]) == 1)
		{
			while (str[i] && is_space(str[i]) == 1)
				i++;
			j = i;
		}
		if (str[i] && i == j && is_metacharacter(str[i]) == 1)
		{
			i++;
			if (str[i] && str[i] == str[j])
			{
				i++;
				add_node(data, str, i, j);
				while (str[i] && is_space(str[i]) == 1)
					i++;
				if (str[i])
					j = i;
				else
					break ;
			}
			else
			{
				add_node(data, str, i, j);
			}
			while (str[i] && is_space(str[i]) == 1)
				i++;
			j = i;
			i--;
		}
		if (str[i] && i == j && str[i] == '\"')
		{
			i++;
			if (str[i])
				j = i;
			else
				break ;
			while (str[i] != '\"')
			{
				i++;
			}
			if (str[i] == '\"')
			{
				add_node(data, str, i, j);
				i++;
				if (str[i])
				{
					j = i;
					i--;
				}
				else
					break ;
			}
		}
		i++;
	}
	if (j != i && is_space(str[j]) == 0 && str[i])
		add_node(data, str, i, j);
	free (str);
}
*/