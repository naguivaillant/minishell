/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 11:49:19 by nassm             #+#    #+#             */
/*   Updated: 2023/10/12 08:31:11 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	h_dollar(t_token *current, t_minishell *minishell)
{
	while (current)
	{
		if (current->cmd != NULL && contain_dollar(current))
		{
			if (handle_dollar(current, minishell) == -1)
				return (-1);
		}
		current = current->next_token;
	}
	return (0);
}

int	ctrlc_heredoc(t_exec **exec, t_minishell **minishell)
{
	free_exec(*exec);
	(*minishell)->exit_code = 130;
	return (130);
}

void	return_exit_code(t_exec **exec, int *exitc,
			t_minishell **minishell, bool pipe)
{
	if ((*exec)->cmd != NULL || ((*exec)->cmd && (*exec)->cmd[0] == '\0'))
		(*exec)->args = get_command_args((*exec)->cmd, CMD);
	if (check_wait_for_pids((*exec), pipe) == true)
		(*exitc) = wait_for_pids(*exec);
	else
		(*exitc) = (*minishell)->exit_code;
}

void	execute_norm(t_minishell **minishell, t_exec **exec,
			int *exitc, bool pipe)
{
	execute_core(minishell, *exec);
	return_exit_code(exec, exitc, minishell, pipe);
	close_all_existing_fds(*exec);
}

int	execute(t_token **token, t_minishell **minishell)
{
	t_token	*current;
	t_exec	*exec;
	t_exec	*tmp;
	int		exitc;
	bool	pipe;

	pipe = false;
	current = *token;
	exitc = 0;
	if (h_dollar(current, *minishell) == -1)
	{
		free_token(&current);
		return (1);
	}
	exec = init_exec(token, &pipe);
	if (*token)
		free_token(token);
	if (handle_heredoc(&exec, *minishell) == -130)
		return (ctrlc_heredoc(&exec, minishell));
	tmp = exec;
	execute_norm(minishell, &exec, &exitc, pipe);
	if (tmp)
		free_exec(tmp);
	return (exitc);
}
