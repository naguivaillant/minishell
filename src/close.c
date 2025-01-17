/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagvaill <nagvaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:30:05 by nagvaill          #+#    #+#             */
/*   Updated: 2023/10/10 15:30:47 by nagvaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	close_fd(int *fd)
{
	if (*fd == STDOUT_FILENO)
		return (0);
	if (*fd == STDIN_FILENO)
		return (0);
	if (*fd < 0)
		return (-1);
	if (close(*fd) == -1)
		return (-1);
	*fd = -1;
	return (0);
}

void	close_all_existing_fds(t_exec *head)
{
	while (head)
	{
		if (head->in != STDIN_FILENO)
		{
			close_fd(&head->in);
		}
		if (head->out != STDOUT_FILENO)
		{
			close_fd(&head->out);
		}
		if (head->here_docfd != STDIN_FILENO)
			close_fd(&head->here_docfd);
		close_fd(&head->here_docfds[0]);
		close_fd(&head->here_docfds[1]);
		close_fd(&head->fds[0]);
		close_fd(&head->fds[1]);
		head = head->next;
	}
}
