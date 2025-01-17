/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_quater.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 07:15:07 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/12 07:31:08 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**append_cmd(char **tab, char *input, int start_index, int last_index)
{
	int		i;
	int		j;
	char	*cmd;

	i = 0;
	j = 0;
	while (input && separator(input[j]) && j < (int)ft_strlen(input))
		j++;
	if ((int)ft_strlen(input) == j)
		return (NULL);
	if (ft_strlen(input) == 1 && (input[0] == ':' || input[0] == '!'))
		return (NULL);
	cmd = copy_part_str(input, start_index, last_index);
	if (!tab)
		tab = append_cmd_norm(tab, cmd);
	else
	{
		while (tab[i] != NULL)
			i++;
		ft_add_str_to_tab(&tab, i, cmd);
	}
	free(cmd);
	return (tab);
}

bool	all_separator(char *str, int start, int i)
{
	while (str && str[start] && separator(str[start]))
		start++;
	if (i != start)
		return (false);
	else
		return (true);
}

int	skip_quotes(char *input, int index)
{
	char	quote_to_skip;

	quote_to_skip = input[index];
	index++;
	while (input[index] != quote_to_skip)
		index++;
	index++;
	return (index);
}
