/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:37:11 by nassm             #+#    #+#             */
/*   Updated: 2023/10/12 08:23:16 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_global_signal(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sigint_receivedived = SIGINT;
	}
}

void	handle_fork_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_sigint_receivedived = SIGINT;
	}
	else if (sig == SIGQUIT)
	{
		ft_fprintf(2, "Quit (core dumped)\n");
		g_sigint_receivedived = SIGQUIT;
	}
}

void	handle_heredoc_signal(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "here_doc\n", 9);
		rl_replace_line("", 0);
		rl_redisplay();
		close(STDIN_FILENO);
		g_sigint_receivedived = SIGINT;
	}
}
