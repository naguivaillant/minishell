/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagvaill <nagvaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:15:58 by nagvaill          #+#    #+#             */
/*   Updated: 2023/06/19 20:28:35 by nagvaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_process(t_data *data, t_exec *exec)
{

	if (builtins_finder(exec->cmd))
		exec_builtins(data, exec->cmd, exec);
	if (exec->cmd[0])
		exec->cmd_state = cmd_final_state(data, exec->cmd[0]);
	if (exec->cmd)
	{
		fprintf(stderr, "ma grosse teub\n");
		safe_exe(data, exec);
	}
	child_aux(exec);
	exit(127);
}

void	waitin(t_data *data, t_exec *exec)
{
	int	i;

	i = -1;
	while (++i < data->pipes)
	{
		waitpid(exec->pid, &exec->status, 0);
		if (WIFEXITED(exec->status))
			exec->status = WEXITSTATUS(exec->status);
	}
}

void	parent_process(t_data *data, t_exec *exec)
{
	safe_close(exec->fdout);
	if (data->prev_pipe != -1)
		safe_close(data->prev_pipe);
	data->prev_pipe = exec->fdin;
}

int	pipex(t_exec *exec)
{
	int		i;

	if (pipex_aux(data, read))
		return (-1);
	else if (data->nbcmd == 1 && is_a_built(env, data))
		return (exec_solo_built(env, data));
	safe_close(data->pipefd[0]);
	waitin(data);
	return (data->status);
}