/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:37:26 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/12 06:44:44 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	check_fpathcommad(char *full_path_command)
{
	if (ft_strcmp(full_path_command, "127") == 0 || ft_strcmp(full_path_command,
			"1") == 0 || ft_strcmp(full_path_command, "126") == 0
		|| ft_strcmp(full_path_command, "2") == 0)
		return (true);
	return (false);
}

void	error_redir(t_minishell **minishell, t_exec **head, int r_pinput,
		t_exec **exec)
{
	t_exec	*current;

	current = *head;
	if (r_pinput == 1 || r_pinput == 2)
	{
		while (current)
		{
			close_all_existing_fds(current);
			current = current->next;
		}
		close_all_existing_fds(*exec);
		free_minishell(*minishell);
		if (*head)
			free_exec(*head);
		if (r_pinput == 2)
			ft_fprintf(2, "ambigious redirection \n");
		exit(r_pinput);
	}
}

void	check_full_path_command(t_minishell **minishell, t_exec **head,
		char *full_path_command, char ***path)
{
	int	ecode;

	ecode = 0;
	if (g_sigint_receivedived == SIGQUIT)
		ecode = 131;
	if (check_fpathcommad(full_path_command))
	{
		ecode = ft_atoi(full_path_command);
		full_path_command = NULL;
		ft_free_tab(*path);
		if (*head)
		{
			free_exec(*head);
		}
		free_minishell(*minishell);
		exit(ecode);
	}
}

void	execute_one_comdnorm(t_exec **exec, t_minishell **minishell,
		t_exec **head)
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

void	execute_one_cmd(t_minishell *minishell, t_exec *head, t_exec *exec)
{
	char	*full_path_command;
	char	**path;
	int		ecode;

	ecode = minishell->exit_code;
	if (g_sigint_receivedived == SIGQUIT)
		ecode = 131;
	execute_one_comdnorm(&exec, &minishell, &head);
	close_all_existing_fds(head);
	path = extract_path(minishell->env);
	full_path_command = get_cmd(path, exec->args[0]);
	check_full_path_command(&minishell, &head, full_path_command, &path);
	execve(full_path_command, exec->args, minishell->env);
	ft_free_tab(path);
	if (full_path_command != NULL)
		free(full_path_command);
	full_path_command = NULL;
	if (exec)
		free_exec(exec);
	free_minishell(minishell);
	exit(ecode);
}
