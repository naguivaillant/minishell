/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:20:24 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/11 16:26:20 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	check_wait_for_pids(t_exec *exec, bool pipe)
{
	if (exec->args && (pipe == true || exec->cmd == NULL \
	|| !is_builtin(exec->args[0]) \
	|| (is_builtin(exec->args[0]) && (exec->infile != NULL \
	|| exec->outfile != NULL))))
		return (true);
	return (false);
}

int	close_handle_heredoc(t_exec **head)
{
	close_fd(&((*head)->here_docfds[0]));
	close_fd(&(*head)->in);
	close_fd(&(*head)->fds[1]);
	close_fd(&(*head)->out);
	close_fd(&(*head)->fds[0]);
	return (-130);
}

int	handle_heredoc_norm(int pid, t_exec **head)
{
	waitpid(pid, NULL, 0);
	close((*head)->here_docfds[1]);
	if (g_sigint_receivedived == SIGINT)
		return (close_handle_heredoc(head));
	(*head)->here_docfd = (*head)->here_docfds[0];
	return (0);
}

int	handle_heredoc_normbis(t_exec **head, t_exec **exec,
		t_minishell *minishell)
{
	int	i;
	int	pid;

	i = 0;
	while ((*head)->here_doc[i])
	{
		pipe((*head)->here_docfds);
		if ((*head)->here_docfd != STDIN_FILENO)
			close_fd(&((*head)->here_docfd));
		pid = fork();
		if (pid == 0)
			here_doc((*head)->here_doc[i], head, minishell, exec);
		if (pid > 0)
		{
			if (handle_heredoc_norm(pid, head) == -130)
				return (-130);
			i++;
		}
	}
	return (0);
}

int	handle_heredoc(t_exec **exec, t_minishell *minishell)
{
	t_exec	**head;

	head = exec;
	while (*head)
	{
		if ((*head)->here_doc != NULL)
		{
			if (handle_heredoc_normbis(head, exec, minishell) == -130)
				return (-130);
		}
		head = &((*head)->next);
	}
	return (0);
}
