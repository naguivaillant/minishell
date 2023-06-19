/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:16:16 by nagvaill          #+#    #+#             */
/*   Updated: 2023/06/18 18:37:50 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_is_builtin(t_exec *exec, t_data *data, int i, t_list *path, t_list *pos)
{
	char	*pwd;

	if (ft_strncmp(exec->cmd[i], "echo", 4))
		return (mini_echo(exec));
//	else if (ft_strncmp(exec->cmd[i], "cd", 2))
//		return (run_cd(args));
	else if (ft_strncmp(exec->cmd[i], "unset", 5))
		return (builtin_unset(data, path), 0);
	else if (ft_strncmp(exec->cmd[i], "export", 6))
		return (builtin_export(data, pos));
	else if (ft_strncmp(exec->cmd[i], "exit", 4))
		return (exit_all(data, 0, "message?"), 0);
	else if (ft_strncmp(exec->cmd[i], "pwd", 3))
	{
		pwd = getcwd(NULL, 0);
		ft_putstr_fd(pwd, 1);
		free(pwd);
		ft_putchar_fd('\n', 1);
		return (1);
	}
	else if (ft_strncmp(exec->cmd[i], "env", 3))
		return (print_env(data), 0);
	return (0);
}