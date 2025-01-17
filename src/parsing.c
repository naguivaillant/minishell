/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:28:32 by nassm             #+#    #+#             */
/*   Updated: 2023/10/12 07:14:07 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	norm_tokenize_input(char **input, int *i)
{
	if ((*input)[*i] == '\"' || (*input)[*i] == '\'')
	{
		*i = skip_quotes(*input, *i);
		return (true);
	}
	else if (!is_spe_parsing(*input, *i))
	{
		(*i)++;
		return (true);
	}
	return (false);
}

char	**tokenize_input(char *input)
{
	int		i;
	int		start_index;
	int		last_index;
	char	**tab;

	i = 0;
	start_index = 0;
	tab = NULL;
	while (input[i])
	{
		if (norm_tokenize_input(&input, &i) == false)
		{
			if (i != start_index && !all_separator(input, start_index, i))
				tab = append_cmd(tab, input, start_index, i);
			start_index = i;
			last_index = get_special_end(input, i);
			tab = append_cmd(tab, input, start_index, last_index + 1);
			start_index = last_index + 1;
			i = last_index + 1;
		}
	}
	if (start_index != i)
		tab = append_cmd(tab, input, start_index, i);
	free(input);
	return (tab);
}

t_type	find_type(char *input)
{
	int					index;
	char				*representation;
	t_type				value;
	t_type_description	*all_special_character;
	size_t				lenght;

	index = 0;
	all_special_character = NULL;
	all_special_character = init_spe_pars(all_special_character);
	while (index < 1)
	{
		representation = all_special_character[index].representation;
		lenght = ft_strlen(representation);
		if (strncmp(representation, input, lenght) == 0)
		{
			value = all_special_character[index].type;
			free_spe_pars(&all_special_character);
			return (value);
		}
		index++;
	}
	free_spe_pars(&all_special_character);
	return (CMD);
}

t_token	*set_first_pos(t_token *token)
{
	while (token->prev_token != NULL)
		token = token->prev_token;
	return (token);
}

t_token	*parse_inputs(char *input)
{
	t_token	*token;
	char	**inputs;
	t_token	*head;

	inputs = tokenize_input(input);
	token = tokens_from_cmd(inputs);
	sort_list_token(token);
	free(inputs);
	if (!token)
		return (NULL);
	token = set_first_pos(token);
	head = token;
	while (head)
	{
		head = head->next_token;
	}
	return (token);
}
