/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:16:30 by nagvaill          #+#    #+#             */
/*   Updated: 2023/06/19 16:02:46 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtins_finder(char **cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd[0], "echo", 4))
		return (1);
	else if (!ft_strncmp(cmd[0], "cd", 2))
		return (1);
	else if (!ft_strncmp(cmd[0], "pwd", 3))
		return (1);
	else if (!ft_strncmp(cmd[0], "export", 6))
		return (1);
	else if (!ft_strncmp(cmd[0], "unset", 5))
		return (1);
	else if (!ft_strncmp(cmd[0], "env", 3))
		return (1);
	else if (!ft_strncmp(cmd[0], "exit", 4))
		return (1);
	return (0);
}

void	exec_builtins(t_data *data, char **cmd, t_exec *exec)
{
	char	*pwd;

	pwd = NULL;
	if (!ft_strncmp(cmd[0], "echo", 4))
		mini_echo(data, exec->cmd);
	//	else if (!ft_strncmp(cmd[0], "cd", 2))
	//		cd_cmd();
	else if (!ft_strncmp(cmd[0], "pwd", 3))
	{
		pwd = getcwd(NULL, 0);
		ft_putstr_fd(pwd, 1);
		free(pwd);
		ft_putchar_fd('\n', 1);
	}
	else if (!ft_strncmp(cmd[0], "export", 6))
		builtin_export(data, exec->cmd);
	else if (!ft_strncmp(cmd[0], "unset", 5))
	{
		fprintf(stderr, "exec unset\n");
		// builtin_unset(data, exec->cmd[0]);
	}
	else if (!ft_strncmp(cmd[0], "env", 3))
		print_env(data);
	else if (!ft_strncmp(cmd[0], "exit", 4))
		exit_all(data, 0, "message?");
	else
		return ;
}