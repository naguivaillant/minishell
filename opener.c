/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opener.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagvaill <nagvaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:21:46 by nagvaill          #+#    #+#             */
/*   Updated: 2023/06/19 20:11:40 by nagvaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	file_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	// exit(1);
}

void	open_in(t_exec *exec)
{
	exec->fdin = open(/*nom du fichier*/, O_RDONLY);
	if (exec->fdin < 0)
		file_error(/*nom du fichier*/);
}

void	open_out(t_exec *exec)
{

	exec->fdout = open(/*nom du fichier*/, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (exec->fdout < 0)
		file_error(/*nom du fichier*/);
}
