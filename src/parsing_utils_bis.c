/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 07:07:07 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/12 08:35:00 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_spe_pars(t_type_description **all_special_character)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		free((*all_special_character)[i].representation);
		i++;
	}
	free(*all_special_character);
}

t_type_description	*init_spe_pars(t_type_description *all_special_character)
{
	all_special_character = ft_calloc(3, sizeof(t_type_description));
	if (!all_special_character)
		return (NULL);
	all_special_character[0].type = IS_PIPE;
	all_special_character[0].representation = ft_strdup("|");
	return (all_special_character);
}

bool	is_spe_parsing(char *str, int i)
{
	if (str && str[i] == '|')
		return (true);
	return (false);
}

bool	is_inquote(char *str, int i)
{
	if (is_in_squote(str, i))
		return (true);
	if (is_in_dquote(str, i))
		return (true);
	return (false);
}

int	special_case_redir(char *inputs, int i)
{
	int	save;

	save = i;
	i++;
	while (separator(inputs[i]))
		i++;
	while (inputs[i] && !is_spe_parsing(inputs, i) && !(separator(inputs[i])
			&& !is_inquote(inputs, i)))
	{
		i++;
	}
	return (i - save - 1);
}
