/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_zone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagvaill <nagvaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:20:31 by nagvaill          #+#    #+#             */
/*   Updated: 2023/06/19 20:14:02 by nagvaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	safe_piping(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipefd");
		return (-1);
	}
	return (0);
}

void	safe_exe(t_data *data, t_exec *exec)
{
	if (execve(exec->cmd_state, exec->cmd, data->env_tab) == -1)
	{
		perror("exceve");
		exit(errno);
	}
	fprintf(stderr, "safe_exe");
}

void	safe_close(int fd)
{
	if (close(fd) == -1)
	{
		perror("close");
		exit(errno);
	}
}

void	safe_dup(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror("dup2");
		exit(errno);
	}
}

void	dup_n_close(int oldfd, int newfd)
{
	safe_dup(oldfd, newfd);
	safe_close(oldfd);
}