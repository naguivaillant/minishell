/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:53:38 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/12 06:58:31 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	here_doc_core(t_exec **exec, t_minishell *minishell,
		const char *limiteur, int *c)
{
	char	*buf;

	while (g_sigint_receivedived != SIGINT)
	{
		buf = readline("here_doc> ");
		if (g_sigint_receivedived == SIGINT)
		{
			free(buf);
			break ;
		}
		if (buf == NULL)
		{
			*c = -1;
			break ;
		}
		if (contain_dollar_string(buf) && *c == 0)
			handle_dollar_here_doc(&buf, minishell);
		if (ft_strcmp(buf, limiteur) == 0)
		{
			free(buf);
			break ;
		}
		here_doc_corenorm(exec, &buf);
	}
}

void	here_doc(char *str, t_exec **exec, t_minishell *minishell,
		t_exec **save)
{
	int		c;
	char	**args;
	int		fd;
	t_exec	*current;

	current = *save;
	here_doc_pipe(current);
	fd = dup(STDIN_FILENO);
	args = split_redir(str);
	close_fd(&((*exec)->here_docfds[0]));
	if ((*exec)->here_docfd != STDIN_FILENO)
		close_fd(&((*exec)->here_docfd));
	signal(SIGINT, &handle_heredoc_signal);
	c = check_quote(&args[1]);
	here_doc_core(exec, minishell, args[1], &c);
	ft_free_tab(args);
	if (c == -1)
		ctrld_heredoc(exec, fd, save, minishell);
	if (g_sigint_receivedived == SIGINT)
		ctrlc_inheredoc(exec, fd, save, minishell);
	close_exit_heredoc(exec, fd, save, &minishell);
	exit(EXIT_SUCCESS);
}
