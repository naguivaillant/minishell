/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:53:43 by mrabourd          #+#    #+#             */
/*   Updated: 2023/05/24 16:26:25 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	split_meta(t_data *data, char *str, int *i, int *j)
{
	(*i)++;
	if (str[*i] && *i + 1 < (int)ft_strlen(str) && str[*i] == str[*j])
	{
		while (*i + 1 < (int)ft_strlen(str) && str[*i] == str[*j])
			(*i)++;
		if (*i + 1 < (int)ft_strlen(str))
			add_node(data, str, *i, *j);
		else if (*i + 1 == (int)ft_strlen(str) && str[*i] == str[*j])
		{
			add_node(data, str, *i + 1, *j);
			*j = *i + 1;
			return ;
		}
		else if (*i + 1 == (int)ft_strlen(str) && str[*i] != str[*j])
		{
			add_node(data, str, *i, *j);
			*j = *i;
			return ;
		}
	}
	else if (str[*i] && *i + 1 == (int)ft_strlen(str))
	{
		add_node(data, str, *i + 1, *j);
		*j = (int)ft_strlen(str);
		return ;
	}
	else
		add_node(data, str, *i, *j);
	while (str[*i] && is_space(str[*i]) == 1)
		(*i)++;
	*j = *i;
	(*i)--;
}

static void	split_double_quotes(t_data *data, char *str, int *i, int *j)
{
	(*i)++;
	if (str[*i])
		*j = *i;
	else
		return ;
	while (str[*i] && str[*i] != '\"')
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
	else
		exit_all(data, 1);
}

static void	split_simple_quotes(t_data *data, char *str, int *i, int *j)
{
	(*i)++;
	if (str[*i])
		*j = *i;
	else
		return ;
	while (str[*i] && str[*i] != '\'')
	{
		(*i)++;
	}
	if (str[*i] == '\'')
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
	else
		exit_all(data, 1);
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
		if (str[i] && j != i && (is_metacharacter(str[i]) == 1 
			|| is_space(str[i]) == 1 || str[i] == '\"' || str[i] == '\''))
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
			split_double_quotes(data, str, &i, &j);
		if (str[i] && i == j && str[i] == '\'')
			split_simple_quotes(data, str, &i, &j);
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