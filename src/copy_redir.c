/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:09:31 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/11 14:09:53 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	copy_redirin(t_token **token, t_exec **exec)
{
	int	nb;
	int	i;
	int	j;

	i = 0;
	j = 0;
	nb = count_tab_line((*token)->redirin);
	(*exec)->infile = ft_calloc(nb + 1, sizeof(char *));
	if (!(*exec)->infile)
		return (-1);
	while ((*token)->redirin[i])
	{	
		(*exec)->infile[j] = ft_strdup((*token)->redirin[i]);
		if (!(*exec)->infile[j])
			return (-1);
		i++;
		j++;
	}
	return (0);
}

int	copy_redirout(t_token **token, t_exec **exec)
{
	int	nb;
	int	i;
	int	j;

	i = 0;
	j = 0;
	nb = count_tab_line((*token)->redirout);
	(*exec)->outfile = ft_calloc(nb + 1, sizeof(char *));
	if (!(*exec)->outfile)
		return (-1);
	while ((*token)->redirout[i])
	{	
		(*exec)->outfile[j] = ft_strdup((*token)->redirout[i]);
		if (!(*exec)->outfile[j])
			return (-1);
		i++;
		j++;
	}
	return (0);
}

int	copy_heredoc(t_token **token, t_exec **exec)
{
	int	nb;
	int	i;
	int	j;

	i = 0;
	j = 0;
	nb = count_tab_line((*token)->here_doc);
	(*exec)->here_doc = ft_calloc(nb + 1, sizeof(char *));
	if (!(*exec)->here_doc)
		return (-1);
	while ((*token)->here_doc[i])
	{	
		(*exec)->here_doc[j] = ft_strdup((*token)->here_doc[i]);
		if (!(*exec)->here_doc[j])
			return (-1);
		i++;
		j++;
	}
	return (0);
}
