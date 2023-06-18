/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:16:30 by nagvaill          #+#    #+#             */
/*   Updated: 2023/06/18 17:14:24 by marvin           ###   ########.fr       */
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

void	exec_builtins(char **cmd, t_exec *exec, t_data *data, t_list *pos)
{
	char	*pwd;

	if (!ft_strncmp(cmd[0], "echo", 4))
		mini_echo(exec);
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
		builtin_export(data, pos);
	else if (!ft_strncmp(cmd[0], "unset", 5))
		builtin_unset(data, pos);
	else if (!ft_strncmp(cmd[0], "env", 3))
		print_env(data);
	else if (!ft_strncmp(cmd[0], "exit", 4))
		exit_all(data, 0, "message?");
	else
		return ;
}
