/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:15:58 by nagvaill          #+#    #+#             */
/*   Updated: 2023/06/19 17:47:16 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_process(t_data *data, t_exec *exec)
{
/*	cmd = start_cmd_tab(exec, env, exec->av[i], 2);
	if (!cmd)
	{
		if (exec->here)
			free(exec->here);
		free_exec_env(env, exec, NULL, 1);
		exit(0);
	}*/
	fprintf(stderr, "enfant\n");
	if (builtins_finder(exec->cmd))
		exec_builtins(data, exec->cmd, exec);
	if (exec->cmd[0])
		exec->cmd_state = cmd_final_state(data, exec->cmd[0]);
	fprintf(stderr, "cmd state: %s\n", exec->cmd_state);
	if (exec->cmd /*&& !isntempty(cmd)*/)
		safe_exe(data, exec);
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
	fprintf(stderr, "parent\n");
	safe_close(exec->fdout);
	if (data->prev_pipe != -1)
		safe_close(data->prev_pipe);
	data->prev_pipe = exec->fdin;
}
/*
static	int	verify_min_one(t_exec *exec, t_list *env)
{
//	exec->heredoc = count_hd(read);
//	if (here_alloc(exec))
//		return (-1);
	if (pipex_hd_aux(env, data))
		return (-1);
	if (pipex_heart(env, data) == -1)
	{
	//	free_exec_env(env, exec, NULL, 4); a faire
		return (-1);
	}
	return (0);
}

int	pipex(t_data *data, t_exec *exec)
{
	int		i;
	int		j;

	j = 0;
	if (data->pipes == 1 && is_a_built_na(data, exec))
		return (exec_solo_built(data));
	// if (verify_min_one(exec, env) == -1)
	// 	return (-1);
	while (j < data->pipes)
	{
		safe_close(exec[j].fdin);
		waitin(data, &exec[j]);
		i = -1;
		while (++i < exec[j].heredoc)
			safe_close(exec[j].here[i]);
	//	free_exec_env(env, exec, NULL, 4);
	//	exec->here_cmp = 0;
		j++;
	}
	return (exec->status);
}*/