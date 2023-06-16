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

void	child_aux(t_list *env, t_exec *exec, char **cmd)
{
	ft_putstr_fd(cmd[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	free(data->cmd);
	free_data_env(env, data, cmd, 2);
}

int	pipex_aux(t_data *data, char *read)
{
	if (!data->pid || !data->av)
	{
		if (data->av)
		{
			free_tab(data->av);
			if (data->pid)
				free(data->pid);
		}
		free(data->env);
		return (1);
	}
	return (0);
}

int	pipex_hd_aux(t_list *env, t_data *data)
{
	int	i;

	if (data->here_nb)
	{
		if (here_doc(env, data) || data->status == 130)
		{
			i = -1;
			while (++i < data->here_nb)
				safe_close(data->here[i].pipe[0]);
			free(data->here);
			free_tab(data->av);
			free(data->env);
			free(data->pid);
			return (1);
		}
	}
	return (0);
}
