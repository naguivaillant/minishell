/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_direction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:16:55 by nagvaill          #+#    #+#             */
/*   Updated: 2023/06/18 18:38:48 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_count(char **tab)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (tab[++i])
	{
		if (tab[i][0] == '<' && tab[i][1] == '<')
			count++;
	}
	return (count);
}

void	dup_n_close(int oldfd, int newfd)
{
	safe_dup(oldfd, newfd); //a faire
	safe_close(oldfd); // a faire
}