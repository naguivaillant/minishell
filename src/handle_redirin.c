/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:31:23 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/12 07:27:24 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_quote_redir(char ***tab)
{
	join_quote((tab[1]));
	trim_redir((tab[1]));
}

int	separator_if(char ***tab, int j)
{
	while ((*tab)[1][j])
	{
		if (separator((*tab)[1][j]))
		{
			ft_free_tab(*tab);
			return (2);
		}
		j++;
	}
	return (-1);
}

int	no_redirout(char ***tab, t_exec **exec)
{
	if (handle_redirouts((*tab)[1], exec) == 1)
	{
		ft_free_tab(*tab);
		return (1);
	}
	return (-1);
}

int	handle_redir_error(char ***tab, t_exec **exec)
{
	int	j;

	j = 0;
	if (separator_if(tab, j) == 2)
		return (2);
	if (ft_strlen((*tab)[0]) == 1)
	{
		if (no_redirout(tab, exec) > 0)
			return (1);
	}
	else
	{
		if (handle_redirout_append((*tab)[1], exec) == 1)
			return (1);
	}
	return (-1);
}

int	handle_redirout(t_exec **exec, t_minishell *minishell)
{
	int		i;
	int		c;
	char	**tab;

	i = 0;
	if ((*exec)->outfile != NULL)
	{
		while ((*exec)->outfile[i])
		{
			tab = split_redir((*exec)->outfile[i]);
			if (contain_dollar_string(tab[1]))
				handle_dollar_redir(&tab[1], minishell);
			if (find_quote(tab[1]))
			{
				join_quote(&tab[1]);
				trim_redir(&tab[1]);
			}
			c = handle_redir_error(&tab, exec);
			if (c > 0)
				return (c);
			ft_free_tab(tab);
			i++;
		}
	}
	return (0);
}
