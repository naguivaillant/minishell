/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util_quater.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 07:41:20 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/12 07:46:52 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expurge_tokencmd(char **str)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	expurge_token_cmdmorm(str, &j);
	(*str)[j] = '\0';
	i = 0;
	while (i < (int)ft_strlen(*str) && (*str)[i])
	{
		if (separator((*str)[i]))
			count++;
		i++;
	}
	if (ft_strlen(*str) == 0 || count == (int)ft_strlen(*str))
	{
		free(*str);
		*str = NULL;
	}
}

int	count_redirin(char **tab)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tab[i])
	{
		if (tab[i][0] == '<' && tab[i][1] != tab[i][0])
			count++;
		i++;
	}
	return (count);
}

void	init_token(t_token **token)
{
	(*token)->prev_token = NULL;
	(*token)->next_token = NULL;
	(*token)->redirin = NULL;
	(*token)->redirout = NULL;
	(*token)->redirout = NULL;
	(*token)->here_doc = NULL;
	(*token)->args = NULL;
	(*token)->cmd = NULL;
}

t_token	*new_token(char *input)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	init_token(&token);
	if (ft_strlen(input) == 1 && (input[0] == ':' || input[0] == '!'))
		return (free_token(&token), NULL);
	else
		token->cmd = input;
	if (find_redir(token->cmd) && (token))
		handle_redir(&token);
	if (token->cmd == NULL && token->redirin == NULL && token->redirout == NULL
		&& token->here_doc == NULL)
		return (free_token(&token), NULL);
	if (token->cmd != NULL)
		token->type = find_type(input);
	else
		token->type = CMD;
	if (token->type == CMD && (token->cmd != NULL || (token->cmd != NULL
				&& token->cmd[0] == '\0')))
		token->args = get_command_args(token->cmd, token->type);
	return (token);
}
