/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:02:39 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/12 06:40:15 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_token_norm(t_minishell **minishell, t_exec *head, t_exec *exec,
		int pid)
{
	if (pid == 0)
	{
		if (exec->args != NULL)
		{
			if (is_builtin(exec->args[0]))
				execute_builtin(*minishell, head, exec);
			else
				execute_one_cmd(*minishell, head, exec);
		}
		else
		{
			close_all_existing_fds(exec);
			free_exec(head);
			free_minishell(*minishell);
			exit(0);
		}
	}
}

void	handle_token(t_minishell **minishell, t_exec *head, t_exec *exec, int i)
{
	int	pid;

	if (exec->cmd != NULL)
	{
		if (exec->cmd != NULL || exec->cmd[0] == '\0')
			exec->args = get_command_args(exec->cmd, 0);
		if (exec->args != NULL && is_builtin(exec->args[0])
			&& exec->next == NULL && i == 0 && exec->infile == NULL
			&& exec->outfile == NULL)
			handle_builtin(minishell, exec, head);
		else
		{
			pid = fork();
			signal(SIGINT, handle_fork_signal);
			signal(SIGQUIT, handle_fork_signal);
			handle_token_norm(minishell, head, exec, pid);
			exec->pid = pid;
		}
		if (exec->args)
		{
			ft_free_tab(exec->args);
			exec->args = NULL;
		}
	}
}
