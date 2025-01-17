/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_pids.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:01:13 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/12 08:34:36 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	wait_for_pids_norm(t_exec **exec, int *wstatus, int *exitc)
{
	while (*exec != NULL)
	{
		waitpid((*exec)->pid, wstatus, 0);
		if (WIFEXITED(*wstatus))
		{
			(*exitc) = WEXITSTATUS(*wstatus);
		}
		*exec = (*exec)->next;
	}
}

int	wait_for_pids(t_exec *exec)
{
	int		wstatus;
	t_exec	*current;
	int		exitc;

	wstatus = 0;
	current = exec;
	exitc = 0;
	while (current != NULL)
	{
		close_all_existing_fds(current);
		current = current->next;
	}
	wait_for_pids_norm(&exec, &wstatus, &exitc);
	if (g_sigint_receivedived == SIGINT)
		exitc = 130;
	if (g_sigint_receivedived == SIGQUIT)
		exitc = 131;
	return (exitc);
}
