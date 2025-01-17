/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:08:14 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/11 14:08:44 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_exec_to_end(t_exec *head, t_exec *new)
{
	while (head->next != NULL)
	{
		head = head->next;
	}
	head->next = new;
}

void	exec_pipe(int pipes[2], t_exec **exec)
{
	pipe(pipes);
	(*exec)->out = pipes[1];
	(*exec)->fds[0] = pipes[0];
}

void	pipe_not_stdin(int pipes[2], t_exec *exec)
{
	exec->in = pipes[0];
	exec->fds[0] = pipes[1];
	pipes[0] = STDIN_FILENO;
}
