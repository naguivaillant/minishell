/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:28:43 by nassm             #+#    #+#             */
/*   Updated: 2023/10/12 06:51:13 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	main_loop_norm(t_minishell **minishell, int exitc)
{
	write(1, "exit\n", 5);
	if (minishell)
	{
		exitc = (*minishell)->exit_code;
		free_minishell(*minishell);
	}
	exit(exitc);
}

void	main_core_loop(char *buff, t_token **token,
			t_minishell **minishell, int exitc)
{
	g_sigint_receivedived = 0;
	add_history(buff);
	(*token) = generate_token(buff, minishell);
	if (*token)
	{
		exitc = execute(token, minishell);
		(*minishell)->exit_code = exitc;
	}
}

void	main_loop(t_minishell **minishell)
{
	char	*buff;
	t_token	*token;
	int		exitc;

	exitc = 0;
	while (true)
	{
		signal(SIGINT, &handle_global_signal);
		signal(SIGQUIT, SIG_IGN);
		buff = readline("minishell$> ");
		if (g_sigint_receivedived == SIGINT)
			(*minishell)->exit_code = 130;
		if (!buff)
			main_loop_norm(minishell, exitc);
		if (buff && ft_strlen(buff) > 0)
			main_core_loop(buff, &token, minishell, exitc);
	}
}

int			g_sigint_receivedived = 0;

int	main(int ac, char **av, char **envp)
{
	t_minishell	*minishell;
	int			exitc;

	minishell = NULL;
	exitc = 0;
	if (ac >= 1 && av[0] != NULL)
	{
		minishell = init_minishell(envp);
		if (minishell != NULL)
		{
			main_loop(&minishell);
			exitc = minishell->exit_code;
			free_minishell(minishell);
		}
	}
	return (exitc);
}
