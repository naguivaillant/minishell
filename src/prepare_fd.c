/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 23:50:26 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/11 23:50:44 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	prepare_input(t_exec **exec, t_minishell *minishell)
{
	if ((*exec)->infile != NULL)
	{
		if (handle_redirin(exec, minishell) == 1)
			return (1);
		if (handle_redirin(exec, minishell) == 2)
			return (2);
	}
	if ((*exec)->here_docfd && (*exec)->here_doclast)
	{
		if ((*exec)->in != STDIN_FILENO)
			close_fd(&((*exec)->in));
		((*exec)->in = (*exec)->here_docfd);
	}
	if ((*exec)->in != STDIN_FILENO)
	{
		dup2((*exec)->in, STDIN_FILENO);
		close((*exec)->in);
	}
	return (0);
}

int	prepare_output(t_exec **exec, t_minishell *minishell)
{
	if ((*exec)->outfile != NULL)
	{
		if (handle_redirout(exec, minishell) == 1)
			return (1);
	}
	if ((*exec)->out != STDOUT_FILENO)
	{
		dup2((*exec)->out, STDOUT_FILENO);
		close((*exec)->out);
	}
	return (0);
}
