/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:13:19 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/12 01:00:52 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	setup_execcmd(t_token **token, t_exec **exec)
{
	(**exec) = (t_exec){0};
	(*exec)->fds[0] = -1;
	(*exec)->fds[1] = -1;
	(*exec)->infile = NULL;
	(*exec)->outfile = NULL;
	(*exec)->out = STDOUT_FILENO;
	(*exec)->infile = NULL;
	(*exec)->here_docfd = STDIN_FILENO;
	(*exec)->here_doclast = (*token)->here_doclast;
	(*exec)->args = NULL;
}

int	token_cmd_norm(t_token **token, t_exec **exec)
{
	if ((*token)->redirin != NULL)
	{
		if (copy_redirin(token, exec) == -1)
			return (-1);
	}
	if ((*token)->redirout)
	{
		if (copy_redirout(token, exec) == -1)
			return (-1);
	}
	if ((*token)->here_doc != NULL)
	{
		if (copy_heredoc(token, exec) == -1)
			return (-1);
	}
	return (0);
}

int	token_cmd_normbis(t_token **token, t_exec **exec)
{
	if ((*token)->cmd != NULL || ft_strlen((*token)->cmd) > 0)
	{
		(*exec)->cmd = ft_strdup((*token)->cmd);
		if (!(*exec)->cmd)
			return (-1);
	}
	else
		(*exec)->cmd = NULL;
	if ((*exec)->cmd && ft_strlen((*exec)->cmd) == 1 \
	&& (*exec)->cmd[0] == ' ')
	{
		free((*exec)->cmd);
		(*exec)->cmd = NULL;
	}
	return (0);
}

int	token_cmd(t_token **token, t_exec **exec, t_exec **head, int pipes[2])
{
	if ((*token)->type == IS_PIPE)
		exec_pipe(pipes, exec);
	if ((*token)->type == CMD)
	{
		*exec = ft_calloc(1, sizeof(t_exec));
		if (!(*exec))
			return (-1);
		setup_execcmd(token, exec);
		if (pipes[0] != STDIN_FILENO)
			pipe_not_stdin(pipes, *exec);
		else
			(*exec)->in = STDIN_FILENO;
		if (token_cmd_norm(token, exec) == -1)
			return (-1);
		if (token_cmd_normbis(token, exec) == -1)
			return (-1);
		if (*head == NULL)
			*head = *exec;
		else
			add_exec_to_end(*head, *exec);
	}
	return (0);
}
