/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:28:44 by mrabourd          #+#    #+#             */
/*   Updated: 2023/05/24 16:25:58 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	len_is_one(t_list *tmp)
{
	if (tmp->content[0] == '|')
		tmp->type = PIPE;
	if (tmp->content[0] == '<')
		tmp->type = REDIRECT_INPUT;
	if (tmp->content[0] == '>')
		tmp->type = REDIRECT_OUTPUT;
	if (tmp->content[0] == '&')
		tmp->type = EPERLUETTE;
	if (tmp->content[0] == '(' || tmp->content[0] == ')')
		tmp->type = PARENTHESIS;
	if (tmp->content[0] == ';')
		tmp->type = SEMICOLON;
	if (tmp->content[0] == ' ')
		tmp->type = BLANCK;
}

void	assign_type(t_data *data)
{
	t_list	*tmp;
	int		i;

	tmp = data->token_list;
	i = 0;
	while (tmp != NULL)
	{
		if (ft_strlen(tmp->content) == 1)
			len_is_one(tmp);
		if (tmp->content[0] == '$')
			tmp->type = DOLLAR;
		if (tmp->content[0] == '-')
			tmp->type = OPTION;
		tmp = tmp->next;
	}
}