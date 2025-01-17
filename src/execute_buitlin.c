/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_buitlin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:54:51 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/12 01:24:48 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_redir(t_exec **exec, t_minishell **minishell, t_exec **head)
{
	int	r_pinput;
	int	r_poutput;

	r_pinput = 0;
	r_poutput = 0;
	r_pinput = prepare_input(exec, *minishell);
	r_poutput = prepare_output(exec, *minishell);
	error_redir(minishell, head, r_pinput, exec);
	error_redir(minishell, head, r_poutput, exec);
}

void	execute_builtin(t_minishell *minishell, t_exec *head, t_exec *exec)
{
	int	ecode;

	check_redir(&exec, &minishell, &head);
	close_all_existing_fds(head);
	if (ft_strcmp(exec->args[0], "echo") == 0)
		ecode = commande_echo(exec->args);
	if (ft_strcmp(exec->args[0], "cd") == 0)
	{
		ecode = commande_cd(exec->args);
	}
	if (ft_strcmp(exec->args[0], "pwd") == 0)
		ecode = commande_pwd();
	if (ft_strcmp(exec->args[0], "export") == 0)
		ecode = commande_export(exec->args, minishell);
	if (ft_strcmp(exec->args[0], "unset") == 0)
		ecode = commande_unset(exec->args, &minishell);
	if (ft_strcmp(exec->args[0], "env") == 0)
		ecode = commande_env(minishell, exec->args);
	if (ft_strcmp(exec->args[0], "exit") == 0)
		ecode = commande_exit(exec->args, minishell, exec, head);
	free_minishell(minishell);
	free_exec(head);
	exit(ecode);
}
