/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagvaill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:26:02 by nagvaill          #+#    #+#             */
/*   Updated: 2023/06/16 13:37:41 by nagvaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_aux(t_exec *exec, char **cmd)
{
	ft_putstr_fd(cmd[0], STDERR_FILENO);
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
//	if (exec->here_nb)
//	{
//		if (here_doc(exec) || exec->status == 130)
//		{
//			i = -1;
//			while (++i < exec->here_nb)
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
