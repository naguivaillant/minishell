/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagvaill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:15:58 by nagvaill          #+#    #+#             */
/*   Updated: 2023/06/16 14:27:25 by nagvaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_process(t_exec *exec, t_list *env, int i)
{
	char	**cmd;

	exec->index = i;
	free(exec->pid);
/*	cmd = start_cmd_tab(exec, env, exec->av[i], 2);
	if (!cmd)
	{
		if (exec->here)
			free(exec->here);
		free_exec_env(env, exec, NULL, 1);
		exit(0);
	}*/
	if (builtins_finder(cmd))
		exec_builtins(cmd, exec, env, 1);
	if (cmd[0])
		exec->cmd_state = cmd_final_state(exec, cmd[0]);
	if (exec->cmd /*&& !isntempty(cmd)*/)
		safe_exe(exec, cmd, exec->env);
	child_aux(env, exec, cmd);
	exit(127);
}

void	waitin(t_exec *exec)
{
	int	i;

	i = -1;
	while (++i < exec->nbcmd)
	{
		waitpid(exec->pid[i], &exec->status, 0);
		if (WIFEXITED(exec->status))
			exec->status = WEXITSTATUS(exec->status);
	}
}

void	parent_process(t_exec *exec)
{
	safe_close(exec->pipefd[1]);
	if (exec->prev_pipe != -1)
		safe_close(exec->prev_pipe);
	exec->prev_pipe = exec->pipefd[0];
}

static	int	verify_min_one(t_exec *exec, t_list *env, char *read)
{
//	exec->here_nb = count_hd(read);
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

int	pipex(char *read, t_list *env)
{
	t_exec	*exec;
	int		i;

	//exec = starton(); // init la struct a faire
	if (struct_init(exec, env, read))
		return (-1);
	else if (exec->nbcmd == 1 && is_a_built(env, exec))
		return (exec_solo_built(env, exec));
	if (verify_min_one(exec, env, read) == -1)
		return (-1);
	safe_close(exec->pipefd[0]); // a faire
	waitin(exec);
	i = -1;
	while (++i < exec->here_nb)
		safe_close(exec->here[i].pipe[0]); //
//	free_exec_env(env, exec, NULL, 4);
//	exec->here_cmp = 0;
	return (exec->status);
}
