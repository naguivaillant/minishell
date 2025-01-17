/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 07:34:08 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/12 07:46:11 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_heredoc(char *str)
{
	if (str && str[0] == '<')
	{
		if (str[1] && str[1] == '<')
			return (true);
	}
	return (false);
}

bool	is_redirout(char *str)
{
	if (str && str[0] == '>')
		return (true);
	return (false);
}

void	find_lastredirin(int lines, char **tab, t_token **token)
{
	while (lines >= 0 && tab[lines])
	{
		if (is_redirin(tab[lines]))
		{
			(*token)->here_doclast = false;
			break ;
		}
		if (is_heredoc(tab[lines]))
		{
			(*token)->here_doclast = true;
			break ;
		}
		lines--;
	}
}

void	implement_redir(t_token **token, char **tab)
{
	int	i;
	int	j;
	int	k;
	int	l;
	int	lines;

	i = 0;
	j = 0;
	k = 0;
	l = 0;
	while (tab[i])
	{
		if (is_redirin(tab[i]))
			(*token)->redirin[j++] = ft_strdup(tab[i]);
		if (is_heredoc(tab[i]))
			(*token)->here_doc[k++] = ft_strdup(tab[i]);
		if (is_redirout(tab[i]))
			(*token)->redirout[l++] = ft_strdup(tab[i]);
		i++;
	}
	lines = i - 1;
	find_lastredirin(lines, tab, token);
}

void	expurge_token_cmdmorm(char **str, int *j)
{
	int	i;

	i = 0;
	while ((*str) && (*str)[i])
	{
		if (((*str)[i] == '<' || (*str)[i] == '>') && !is_inquote(*str, i))
		{
			i++;
			while (i < (int)(ft_strlen(*str)) && (*str)[i]
				&& (*str)[i] == (*str)[i - 1])
				i++;
			if ((*str)[i] && separator((*str)[i]))
			{
				while ((*str)[i] && separator((*str)[i]))
					i++;
			}
			while ((*str)[i] && !separator((*str)[i]))
				i++;
		}
		else
		{
			(*str)[(*j)++] = (*str)[i++];
		}
	}
}
