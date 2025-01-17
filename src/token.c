/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 23:56:47 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/12 07:47:29 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*get_token_bottom(t_token *token)
{
	while (token && token->next_token != NULL)
		token = token->next_token;
	return (token);
}

void	token_add_bottom(t_token **token, t_token *new_token)
{
	t_token	*bottom;

	if (!new_token)
		return ;
	if (!*token)
	{
		*token = new_token;
		return ;
	}
	bottom = get_token_bottom(*token);
	new_token->prev_token = bottom;
	bottom->next_token = new_token;
}

bool	is_full_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!separator(str[i]))
			return (false);
		i++;
	}
	return (true);
}

t_token	*create_token(char **inputs, int nb)
{
	t_token	*token;
	int		i;

	token = NULL;
	i = 0;
	while (i < nb)
	{
		if (i == 0 && !is_full_space(inputs[i]))
			token = new_token(inputs[i]);
		else if (!is_full_space(inputs[i]))
			token_add_bottom(&token, new_token(inputs[i]));
		i++;
	}
	return (token);
}

t_token	*tokens_from_cmd(char **inputs)
{
	t_token	*token;
	int		nb_tokens;

	nb_tokens = count_tab_line(inputs);
	token = create_token(inputs, nb_tokens);
	return (token);
}
