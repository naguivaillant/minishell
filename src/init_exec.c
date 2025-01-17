/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:16:12 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/12 06:39:28 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_exec_norm(t_token *current, int *pipes, t_exec **exec, bool *pipe)
{
	if ((current)->type == IS_PIPE)
	{
		*pipe = true;
		exec_pipe(pipes, exec);
	}
}

int	init_exec_normbis(t_token **current, t_exec **exec, t_exec **head,
		int *pipes)
{
	if ((*current)->type == CMD)
	{
		if (token_cmd(current, exec, head, pipes) == -1)
			return (-1);
	}
	return (0);
}

t_exec	*init_exec(t_token **token, bool *pipe)
{
	t_exec	*head;
	t_exec	*exec;
	t_token	*current;
	int		pipes[2];

	head = NULL;
	exec = NULL;
	current = *token;
	pipes[0] = STDIN_FILENO;
	pipes[1] = STDOUT_FILENO;
	while (current)
	{
		init_exec_norm(current, pipes, &exec, pipe);
		if (init_exec_normbis(&current, &exec, &head, pipes) == -1)
		{
			free_exec(head);
			return (NULL);
		}
		if (!(current))
			break ;
		(current) = (current)->next_token;
	}
	return (head);
}
