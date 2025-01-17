/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 07:03:20 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/12 08:22:07 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	separator(char c)
{
	if (ft_strchr(" \t\r\v\f\n", c) == NULL)
		return (false);
	else
		return (true);
}

int	count_tab_line(char **tab)
{
	int	i;

	i = 0;
	if (!tab || !(*tab))
		return (0);
	while (tab[i])
	{
		i++;
	}
	return (i);
}

t_type_description	*init_representation(t_type_description *all_special_char)
{
	all_special_char = ft_calloc(NUMBER_OF_SPECIAL_CHARACTER,
			sizeof(t_type_description));
	if (!all_special_char)
		return (NULL);
	all_special_char[0].type = IS_PIPE;
	all_special_char[0].representation = ft_strdup("|");
	all_special_char[1].type = AND;
	all_special_char[1].representation = ft_strdup("&&");
	all_special_char[2].type = OUT_APPEND;
	all_special_char[2].representation = ft_strdup(">>");
	all_special_char[3].type = HERE_DOC;
	all_special_char[3].representation = ft_strdup("<<");
	all_special_char[4].type = REDIR_IN;
	all_special_char[4].representation = ft_strdup("<");
	all_special_char[5].type = OUT;
	all_special_char[5].representation = ft_strdup(">");
	return (all_special_char);
}

void	free_description(t_type_description **all_special_character)
{
	int	i;

	i = 0;
	while (i < NUMBER_OF_SPECIAL_CHARACTER)
	{
		free((*all_special_character)[i].representation);
		i++;
	}
	free(*all_special_character);
}

bool	is_special_character(char c)
{
	int					index;
	t_type_description	*all_special_character;

	all_special_character = NULL;
	all_special_character = init_representation(all_special_character);
	index = 0;
	while (index < NUMBER_OF_SPECIAL_CHARACTER)
	{
		if (all_special_character[index].representation[0] == c)
		{
			free_description(&all_special_character);
			return (true);
		}
		index++;
	}
	free_description(&all_special_character);
	return (false);
}
