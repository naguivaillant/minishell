/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:32:12 by mrabourd          #+#    #+#             */
/*   Updated: 2023/05/15 16:59:17 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strchrint(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (c == '\0')
		return (ft_strlen(s));
	return (-1);
}

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
	return (i);
}

void	add_str(t_data *data)
{
	
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
		exit_all(data); /*--> check bash pour savoir comment gerer quand nb de quotes est impair*/
	if (quotes == 0)
	{
		data->cmd = ft_split(str, ' ');
		fill_cmd_list(&data);
		return ;
	}  
	if (quotes % 2 == 0)
	{
		pos = ft_strchrint(data->input, "\"");
		str = ft_split(data->input, "\"");
		if (pos != 0)/*ca veut dire que le 1er quote n'est pas au debut des commandes donc on peut split le debut*/
		{
			data->cmd = ft_split(str[i], " ");
			
		}
	}
}