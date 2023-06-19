/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:26:02 by nagvaill          #+#    #+#             */
/*   Updated: 2023/06/19 17:31:29 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_aux(t_exec *exec)
{
	ft_putstr_fd(exec->cmd[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	free(exec->cmd);
}

int	pipex_aux(t_exec *exec)
{
	if (!exec->pid || !exec->cmd)
	{
		if (exec->cmd)
		{
			free_tab(exec->cmd);
//			if (exec->pid)
//				free(exec->pid);
		}
		return (1);
	}
	return (0);
}

int	pipex_hd_aux(t_exec *exec)
{
	int	i;

	i = exec->status;
//	if (exec->heredoc)
//	{
//		if (here_doc(exec) || exec->status == 130)
//		{
//			i = -1;
//			while (++i < exec->heredoc)
//				safe_close(exec->here[i].pipe[0]);
//			free(exec->here);
//			free_tab(exec->cmd);
//			free(data->env);
//			free(exec->pid);
//			return (1);
//		}
//	}
	return (i);
}