#include "../include/minishell.h"

int	exec_solo_built(t_data *data)
{
	data->exec[0].builtin = dup(STDIN_FILENO);
	data->exec[0].builtout = dup(STDOUT_FILENO);
	exec_builtins(data, data->exec[0].cmd, &data->exec[0]);
	// free_tab(data->exec[0].cmd);
	// free(data->exec[0].pid);
	// free(data->env);
	dup_n_close(data->exec[0].builtin, STDIN_FILENO);
	dup_n_close(data->exec[0].builtout, STDOUT_FILENO);
	return (0);
}

int	exec(t_data *data, t_exec *exec)
{
	exec->pid = fork();
	if (exec->pid == 0)
	{
		child_process(data, exec);
	}
	else if (exec->pid > 0)
	{
		parent_process(data, exec);
	}
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
		printf("exec[j]: %s\n", data->exec[j].cmd[0]);
		if (is_a_built_na(data, &data->exec[j]))
			waitpid(data->exec[j].pid, &data->exec[j].status, 0);
		// if (exec->heredoc && ft_strstr(exec->cmd[i], "<<"))
		// 	exec->here_cmp++;
		j++;
	}
	return (0);
}