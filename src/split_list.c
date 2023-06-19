/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:53:43 by mrabourd          #+#    #+#             */
/*   Updated: 2023/06/19 17:59:51 by mrabourd         ###   ########.fr       */
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

char	*extract_variable(t_data *data, char *str, int *i, int *j)
{
	char	*variable;

	variable = NULL;
	while (str[*i] && str[*i] != '\"')
		(*i)++;
	variable = malloc(sizeof(char) * ((*i - *j) + 1));
	if (variable == NULL)
		exit_all(data, 1, "problem malloc variable split list");
	ft_strlcpy(variable, &str[*j], ((*i - *j) + 1));
	printf("i extract: %d\n", *i);
	printf("j extract: %d\n", *j);
	return (variable);
}

static void	add_variable_quoted(t_data *data, char *str, int i, int j)
{
	t_list	*tmp;
	char	*variable;

	variable = NULL;
	tmp = data->token_list;
	printf("i add1: %d\n", i);
	printf("j add1: %d\n", j);
	(i)++;
	if (str[i])
		j = i;
	else
		return ;
	while (tmp->next != NULL)
		tmp = tmp->next;
	variable = extract_variable(data, str, &i, &j);
	i += ft_strlen(variable);
	j += ft_strlen(variable);
	// printf("i add2: %d\n", i);
	printf("j add2: %d\n", j);
	printf("tmp->content: %s\n", tmp->content);
	tmp->content = ft_strjoin(tmp->content, variable);
	tmp->type = ENVIRONMENT_VARIABLE;
	free(variable);
}

static void	split_double_quotes(t_data *data, char *str, int *i, int *j)
{
	int	quote;

	quote = 0;
	if (str[*i - 1] == '=')
	{
		printf("ok\n");
		add_variable_quoted(data, str, *i, *j);
		printf("i: %d\n", *i);
		printf("j: %d\n", *j);
		return ;
	}
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
		add_node_double_quote(data, str, *i, *j);
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
		exit_all(data, 1, "There is a double quote missing");
}

static void	split_single_quotes(t_data *data, char *str, int *i, int *j)
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
		add_node_single_quote(data, str, *i, *j);
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
		exit_all(data, 1, "There is a single quote missing");
}

/* A NORMER */
void	split_in_list(t_data *data, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
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
			split_single_quotes(data, str, &i, &j);
		i++;
	}
	if (j != i && is_space(str[j]) == 0)
		add_node(data, str, i, j);
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