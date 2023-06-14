#include "../include/minishell.h"

int	builtins_finder(char **cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd[0], "echo"))
		return (1);
	else if (!ft_strcmp(cmd[0], "cd"))
		return (1);
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (1);
	else if (!ft_strcmp(cmd[0], "export"))
		return (1);
	else if (!ft_strcmp(cmd[0], "unset"))
		return (1);
	else if (!ft_strcmp(cmd[0], "env"))
		return (1);
	else if (!ft_strcmp(cmd[0], "exit"))
		return (1);
	return (0);
}

void	exec_builtins(char **cmd)
{
	if (!ft_strcmp(cmd[0], "echo"))
		echo_cmd();
	else if (!ft_strcmp(cmd[0], "cd"))
		cd_cmd();
	else if (!ft_strcmp(cmd[0], "pwd"))
		pwd_cmd();
	else if (!ft_strcmp(cmd[0], "export"))
		export_cmd();
	else if (!ft_strcmp(cmd[0], "unset"))
		unset_cmd();
	else if (!ft_strcmp(cmd[0], "env"))
		env_cmd();
	else if (!ft_strcmp(cmd[0], "exit"))
		exit_cmd();
	else
		return ;
}
