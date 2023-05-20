/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:32:12 by mrabourd          #+#    #+#             */
/*   Updated: 2023/05/20 17:44:00 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_quotes(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			quote++;
		i++;
	}
	return (quote);
}

void	parse_cmd(t_data *data)
{
	int		i;
	char	**str;
	int		quotes;
	int		pos;

	pos = 0;
	i = 0;
	str = NULL;
	quotes = check_quotes(data->input);
	if (quotes % 2 != 0)
		exit_all(data, 1); /*--> check bash pour savoir comment gerer quand nb de quotes est impair*/
	split_in_list(data, data->input);
	// print_all(data);
	// assign_type(data);
}