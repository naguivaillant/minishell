/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_env_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 18:57:18 by mrabourd          #+#    #+#             */
/*   Updated: 2023/06/18 19:03:05 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*extract_name(t_data *data, t_list *variable)
{
	char	*name;
	int		i;

	i = 0;
	name = NULL;
	variable->type = VARIABLE_NAME;
	while (variable->content[i] != '=')
		i++;
	name = malloc(sizeof(char) * (i + 1));
	if (name == NULL)
		exit_all(data, 1, "Problem of malloc when check variable (export)");
	ft_strlcpy(name, variable->content, (i + 1));
	return (name);
}

void	assign_variable_name(t_data *data, t_list *current)
{
	t_list *tmp;
	char	*name;

	name = NULL;
	tmp = current;
	if (tmp->next)
	{
		tmp = tmp->next;
		if (ft_strchr(tmp->content, '=') != 0)
			tmp->type = ENVIRONMENT_VARIABLE;
		name = extract_name(data, tmp->content);
	}
}