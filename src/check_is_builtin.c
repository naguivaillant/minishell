#include "minishell.h"

int	check_is_builtin(t_data data, int i)
{
	char	*pwd;

	if (ft_strncmp(data->cmd[i], "echo", 4))
		return (mini_echo(data));
	else if (ft_strncmp(data->cmd[i], "cd", 2))
		return (run_cd(args));
	else if (ft_strncmp(data->cmd[i], "unset", 5))
		return (run_unset(args));
	else if (ft_strncmp(data->cmd[i], "export", 6))
		return (run_export(args));
	else if (ft_strncmp(data->cmd[i], "exit", 4))
		run_exit(args, copy);
	else if (ft_strncmp(data->cmd[i], "pwd", 3))
	{
		pwd = getcwd(NULL, 0);
		ft_putstr_fd(pwd, 1);
		free(pwd);
		ft_putchar_fd('\n', 1);
		return (1);
	}
	else if (ft_strncmp(data->cmd[i], "env", 3))
		return (run_env());
	return (0);
}
