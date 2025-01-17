/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 06:54:48 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/12 08:20:44 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_dollar_here_doc(char **str, t_minishell *minishell)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
		{
			if ((*str)[i + 1] && ((*str)[i + 1] == '\'' || (*str)[i
					+ 1] == '\"'))
				return ;
		}
		i++;
	}
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$' && !is_in_squote((*str), i) && (ft_isalpha((*str)[i
					+ 1]) || (*str)[i + 1] == '?'))
		{
			(*str) = replace_envar(str, i, minishell);
		}
		i++;
	}
}

int	check_quote(char *str[])
{
	if (find_quote(*str))
	{
		join_quote(str);
		return (1);
	}
	return (0);
}

void	here_doc_corenorm(t_exec **exec, char **buf)
{
	write((*exec)->here_docfds[1], *buf, ft_strlen(*buf));
	write((*exec)->here_docfds[1], "\n", 1);
	free(*buf);
}

bool	contain_dollar_string(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}
