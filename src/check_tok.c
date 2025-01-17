/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagvaill <nagvaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:03:52 by nagvaill          #+#    #+#             */
/*   Updated: 2023/10/10 17:06:17 by nagvaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_redir_tok(t_token *current)
{
	if (current->type == REDIR_IN)
		return (true);
	if (current->type == OUT)
		return (true);
	if (current->type == OUT_APPEND)
		return (true);
	if (current->type == HERE_DOC)
		return (true);
	return (false);
}

bool	check_tok(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == IS_PIPE
			&& (current->prev_token == NULL || current->next_token == NULL))
			return (false);
		if (current->type == IS_PIPE
			&& current->prev_token->type != CMD
			&& current->next_token->type != CMD)
		{
			return (false);
		}
		current = current->next_token;
	}
	return (true);
}
