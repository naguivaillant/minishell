/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirin_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 07:22:56 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/12 07:25:22 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_redirin_bis(char *arg, t_exec **exec)
{
	DIR	*dir;
	int	fd;

	fd = open(arg, O_RDONLY);
	if (find_quote(arg))
		join_quote(&arg);
	dir = opendir(arg);
	if (dir)
	{
		closedir(dir);
		ft_fprintf(2, "%s: Is a directory\n", arg);
		return (1);
	}
	if ((*exec)->in != STDIN_FILENO)
		close_fd(&(*exec)->in);
	if (fd == -1)
	{
		perror(arg);
		(*exec)->in = STDIN_FILENO;
		return (1);
	}
	else
		(*exec)->in = fd;
	return (0);
}

int	handle_dollar_redir(char **str, t_minishell *minishell)
{
	int	i;

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
	return (0);
}

void	trim_redir(char **str)
{
	int	len;

	len = ft_strlen(*str) - 1;
	while (len >= 0)
	{
		if (!separator(len))
			break ;
		len--;
	}
	len++;
	(*str)[len] = '\0';
}

int	check_separator(char ***tab, t_exec **exec)
{
	int	j;

	j = 0;
	while ((*tab)[1][j])
	{
		if (separator((*tab)[1][j]))
		{
			ft_free_tab(*tab);
			return (2);
		}
		j++;
	}
	if (handle_redirin_bis((*tab)[1], exec) == 1)
	{
		ft_free_tab(*tab);
		return (1);
	}
	return (-1);
}

int	handle_redirin(t_exec **exec, t_minishell *minishell)
{
	int		i;
	int		c;
	char	**tab;

	i = -1;
	c = 0;
	if ((*exec)->infile != NULL)
	{
		while ((*exec)->infile[++i])
		{
			tab = split_redir((*exec)->infile[i]);
			if (contain_dollar_string(tab[1]))
				handle_dollar_redir(&tab[1], minishell);
			if (find_quote(tab[1]))
			{
				join_quote(&tab[1]);
				trim_redir(&tab[1]);
			}
			c = check_separator(&tab, exec);
			if (c > 0)
				return (c);
			ft_free_tab(tab);
		}
	}
	return (0);
}
