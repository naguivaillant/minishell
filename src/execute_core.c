/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:11:35 by nassm             #+#    #+#             */
/*   Updated: 2023/10/12 06:41:46 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_builtin(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (true);
	if (ft_strcmp(str, "cd") == 0)
		return (true);
	if (ft_strcmp(str, "pwd") == 0)
		return (true);
	if (ft_strcmp(str, "export") == 0)
		return (true);
	if (ft_strcmp(str, "unset") == 0)
		return (true);
	if (ft_strcmp(str, "env") == 0)
		return (true);
	if (ft_strcmp(str, "exit") == 0)
		return (true);
	return (false);
}

void	handle_builtin(t_minishell **minishell, t_exec *exec, t_exec *head)
{
	if (ft_strcmp(exec->args[0], "echo") == 0)
		(*minishell)->exit_code = commande_echo(exec->args);
	if (ft_strcmp(exec->args[0], "cd") == 0)
		(*minishell)->exit_code = commande_cd(exec->args);
	if (ft_strcmp(exec->args[0], "pwd") == 0)
		(*minishell)->exit_code = commande_pwd();
	if (ft_strcmp(exec->args[0], "export") == 0)
		(*minishell)->exit_code = commande_export(exec->args, *minishell);
	if (ft_strcmp(exec->args[0], "unset") == 0)
		(*minishell)->exit_code = commande_unset(exec->args, minishell);
	if (ft_strcmp(exec->args[0], "env") == 0)
		(*minishell)->exit_code = commande_env(*minishell, exec->args);
	if (ft_strcmp(exec->args[0], "exit") == 0)
		(*minishell)->exit_code = commande_exit(exec->args, *minishell, exec,
				head);
}

void	execute_core(t_minishell **minishell, t_exec *exec)
{
	t_exec	*head;
	int		i;

	head = exec;
	g_sigint_receivedived = 0;
	i = 0;
	while (exec)
	{
		if (exec->cmd != NULL)
			handle_token(minishell, head, exec, i);
		else if (exec->infile != NULL || exec->outfile != NULL
			|| exec->here_doc != NULL)
		{
			if (exec->infile != NULL)
				handle_redirin(&exec, *minishell);
			if (exec->outfile != NULL)
				handle_redirout(&exec, *minishell);
			if (exec->here_doc != NULL)
				handle_redirin(&exec, *minishell);
			close_all_existing_fds(exec);
		}
		exec = exec->next;
		i++;
	}
}
