/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 06:50:39 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/12 07:01:06 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_minishell	*init_minishell(char **envp)
{
	t_minishell	*mini;

	mini = ft_calloc(1, sizeof(t_minishell));
	if (mini != NULL && envp != NULL && *envp != NULL)
	{
		ft_memset(mini, 0, sizeof(t_minishell));
		mini->env = ft_str_arr_dup(envp);
		mini->tmp = NULL;
		mini->exit_code = 0;
		return (mini);
	}
	return (mini);
}

void	generate_token_norm(char *buff, int *count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buff[i])
	{
		if (buff[i] && (buff[i] == '<' || buff[i] == '>'))
		{
			j = i;
			while (buff[i] && buff[i] == buff[j])
			{
				i++;
				(*count)++;
			}
		}
		if ((*count) >= 3)
			break ;
		if (buff[i])
			i++;
	}
}

t_token	*exit_check_tok(t_token **token, t_minishell **minishell)
{
	free_token(token);
	(*minishell)->exit_code = 2;
	return (NULL);
}

t_token	*generate_token(char *buff, t_minishell **minishell)
{
	t_token	*token;
	int		count;

	if (check_redir_args(buff) == false)
	{
		count = 0;
		generate_token_norm(buff, &count);
		if (count >= 3)
			(*minishell)->exit_code = exit_syntax_error_near(buff);
		else
			(*minishell)->exit_code = exit_syntax_error_nl(buff);
		return (NULL);
	}
	if (!is_valid_input(buff) || !has_matching_quotes(buff))
	{
		(*minishell)->exit_code = exit_syntax_error(buff);
		return (NULL);
	}
	token = parse_inputs(buff);
	if (token == NULL)
		return (NULL);
	if (!check_tok(token))
		return (exit_check_tok(&token, minishell));
	return (token);
}
