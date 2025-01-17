/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 06:58:22 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/12 07:00:54 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ctrld_heredoc(t_exec **exec, int fd, t_exec **save,
		t_minishell *minishell)
{
	close_all_existing_fds(*exec);
	close(fd);
	close_fd(&((*exec)->here_docfds[1]));
	free_exec(*save);
	free_minishell(minishell);
	exit(EXIT_SUCCESS);
}

void	ctrlc_inheredoc(t_exec **exec, int fd, t_exec **save,
		t_minishell *minishell)
{
	close_fd(&((*exec)->here_docfds[0]));
	close_fd(&((*exec)->here_docfds[1]));
	dup2(fd, STDIN_FILENO);
	close(fd);
	close_fd(&(*exec)->in);
	close_fd(&(*exec)->fds[1]);
	close_fd(&(*exec)->out);
	close_fd(&(*exec)->fds[0]);
	free_exec(*save);
	free_minishell(minishell);
	exit(-130);
}

void	close_exit_heredoc(t_exec **exec, int fd, t_exec **save,
		t_minishell **minishell)
{
	close(fd);
	close_fd(&((*exec)->here_docfds[1]));
	close_fd(&(*exec)->in);
	close_fd(&(*exec)->fds[1]);
	close_fd(&(*exec)->out);
	close_fd(&(*exec)->fds[0]);
	close_all_existing_fds(*exec);
	if (*exec)
		free_exec(*save);
	if (minishell)
		free_minishell(*minishell);
}

void	here_doc_pipe(t_exec *current)
{
	while (current)
	{
		close_fd(&(current->here_docfd));
		close_fd(&current->in);
		close_fd(&current->out);
		current = current->next;
	}
}
