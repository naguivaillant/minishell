/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_ter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 07:11:10 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/12 07:14:11 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_heredoc_first(t_token **token)
{
	while (*token && (*token)->prev_token != NULL
		&& (*token)->prev_token->type != HERE_DOC)
	{
		if ((*token)->next_token != NULL)
			(*token)->next_token->prev_token = (*token)->prev_token;
		(*token)->prev_token->next_token = (*token)->next_token;
		(*token)->next_token = (*token)->prev_token;
		(*token)->prev_token = (*token)->prev_token->prev_token;
		if ((*token)->prev_token != NULL)
			(*token)->prev_token->next_token = *token;
		(*token)->next_token->prev_token = *token;
	}
}

void	sort_list_token(t_token *token)
{
	while (token)
	{
		if (token->type == HERE_DOC && token->prev_token != NULL
			&& token->prev_token->type != HERE_DOC)
		{
			set_heredoc_first(&token);
			token = token->next_token;
		}
		else
			token = token->next_token;
	}
}

int	get_special_end(char *inputs, int index)
{
	if (is_spe_parsing(inputs, index))
	{
		while (is_spe_parsing(inputs, index))
			index++;
		return (index - 1);
	}
	return (0);
}

char	*copy_part_str(char *input, int start_index, int last_index)
{
	char	*cpy;

	cpy = strndup(&input[start_index], last_index - start_index);
	return (cpy);
}

char	**append_cmd_norm(char **tab, char *cmd)
{
	tab = ft_calloc(2, sizeof(char *));
	if (!tab)
		return (NULL);
	tab[0] = ft_strdup(cmd);
	if (!tab[0])
		return (NULL);
	tab[1] = NULL;
	return (tab);
}
