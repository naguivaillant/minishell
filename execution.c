/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagvaill <nagvaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:43:29 by nagvaill          #+#    #+#             */
/*   Updated: 2023/06/19 20:23:54 by nagvaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_solo_built(t_data *data)
{
	data->exec[0].builtin = dup(STDIN_FILENO);
	data->exec[0].builtout = dup(STDOUT_FILENO);
	exec_builtins(data, data->exec[0].cmd, &data->exec[0]);
	dup_n_close(data->exec[0].builtin, STDIN_FILENO);
	dup_n_close(data->exec[0].builtout, STDOUT_FILENO);
	return (0);
}

int	exec(t_data *data, t_exec *exec)
{
	exec->pid = fork();
	if (exec->pid == 0)
		child_process(data, exec);
	else if (exec->pid > 0)
		parent_process(data, exec);
	return (0);
}

int	is_a_built_na(t_data *data, t_exec *exec)
{
	int		ret;
	(void)data;

	ret = builtins_finder(exec->cmd);
	return (ret);
}

int	pipex_heart(t_data *data)
{
	int	j;

	j = 0;
	while (j < data->pipes)
	{
		if (exec(data, &data->exec[j]) == -1)
			return (-1);
		if (is_a_built_na(data, &data->exec[j]))
			waitpid(data->exec[j].pid, &data->exec[j].status, 0);
		j++;
	}
		waitin(data, data->exec);
	return (0);
}