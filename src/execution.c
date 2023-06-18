#include "minishell.h"

int	exec_solo_built(t_list *env, t_exec *exec)
{
	t_path	path;
	t_list	*pos;
	t_data	*data;
	char	**tab;

	exec->builtin = dup(STDIN_FILENO);
	exec->builtout = dup(STDOUT_FILENO);
	tab = put_cmd_in_tab(data, data->pipes);
	exec_builtins(tab, exec, data, path, pos);
	free_tab(tab);
	free(exec->pid);
	free(exec->env);
	free_tab(exec->cmd);
	dup_n_close(exec->builtin, STDIN_FILENO);
	dup_n_close(exec->builtout, STDOUT_FILENO);
	return (0);
}

int	exec(t_list *env, t_exec *exec, int i)
{
	exec->pid[i] = fork();
	if (exec->pid[i] == 0)
		child_process(exec, env, i);
	else if (exec->pid[i] > 0)
		parent_process(exec);
	return (0);
}

int	is_a_built(t_list *env, t_exec *exec)
{
	char	**tab;
	int		ret;

	tab = put_cmd_in_tab(data, data->pipes);
	ret = builtins_finder(tab);
	if (tab)
		free_tab(tab);
	return (ret);
}

static	int	is_a_built_na(t_list *env, t_exec *exec, int i)
{
	char	**tab;
	int		ret;

	tab = put_cmd_in_tab(data, data->pipes);
	ret = builtins_finder(tab);
	if (tab)
		free_tab(tab);
	return (ret);
}

int	pipex_heart(t_list *env, t_exec *exec)
{
	int	i;

	i = 0;
	while (i + exec->here_doc < exec->nbcmd + exec->here_doc)
	{
		if (exec(env, exec, i) == -1)
			return (-1);
		if (is_a_built_na(env, exec, i))
			waitpid(exec->pid[i], &exec->status, 0);
		// if (exec->here_nb && ft_strstr(exec->cmd[i], "<<"))
		// 	exec->here_cmp++;
		i++;
	}
	return (0);
}
