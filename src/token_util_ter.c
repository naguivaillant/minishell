/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util_ter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 07:37:55 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/12 07:41:48 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_redirout(char **tab)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tab[i])
	{
		if (tab[i][0] == '>')
			count++;
		i++;
	}
	return (count);
}

int	count_heredoc(char **tab)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tab[i])
	{
		if (tab[i][0] == '<' && tab[i][1] == tab[i][0])
			count++;
		i++;
	}
	return (count);
}

void	handle_redir(t_token **token)
{
	char	**tab;
	int		nb_redirin;
	int		nb_redirout;
	int		nb_heredoc;

	nb_redirin = 0;
	nb_redirout = 0;
	tab = NULL;
	tab = create_redirtab((*token)->cmd);
	nb_redirin = count_redirin(tab);
	nb_redirout = count_redirout(tab);
	nb_heredoc = count_heredoc(tab);
	if (nb_redirin > 0)
		(*token)->redirin = ft_calloc(nb_redirin + 1, sizeof(char *));
	if (nb_redirout > 0)
		(*token)->redirout = ft_calloc(nb_redirout + 1, sizeof(char *));
	if (nb_heredoc > 0)
		(*token)->here_doc = ft_calloc(nb_heredoc + 1, sizeof(char *));
	implement_redir(token, tab);
	expurge_tokencmd(&(*token)->cmd);
	ft_free_tab(tab);
}
