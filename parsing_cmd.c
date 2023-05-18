/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:32:12 by mrabourd          #+#    #+#             */
/*   Updated: 2023/05/18 16:32:47 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_metacharacter(char c)
{
	if (c == '|' || c == '&' || c == ';')
		return (1);
	if (c == '(' || c == ')')
		return (1);
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int		is_space(char c)
{
	if (c == ' ' || c == '\t' | c == '\n')
		return (1);
	if (c == '\v' || c == '\f' | c == '\r')
		return (1);
	return (0);
}

// void	replace_input(t_data *data, int add)
// {
// 	char	*new_input;

// 	new_input = NULL;
// 	new_input = malloc (sizeof(char) * (add + ft_strlen(data->input) + 1));
// 	if (new_input == NULL)
// 		free_all(data);
// }

// void	add_space(t_data *data)
// {
// 	int		i;
// 	int		add;

// 	i = 0;
// 	add = 0;
// 	while (data->input[i])
// 	{
// 		if (is_metacharacter(data->input[i]))
// 		{
// 			if (data->input[i - 1] && is_space(data->input[i - 1]) == 0)
// 				add++;
// 			i++;
// 			if (data->input[i] && is_space(data->input[i]) == 0)
// 				add++;
// 		}
// 		i++;
// 	}
// 	if (add == 0)
// 		return ;
// 	replace_input(&data, add);
// }

/*
		-ajouter des espaces entre chaque token// entre les metacharacters : 
				space, tab, newline, ‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, or ‘>’ -> dans str input
			et changer \n ou \t en espace normal
		-separer chaque token en fonction des espaces -> en creant une liste
		-en meme temps, faire en sorte que si un quote est ouvert, le token reste le meme, 
				et ne passe au suivant que quand le prochain quote est trouve
		-si quote pas ferme, incorrect -> free all
*/

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
}