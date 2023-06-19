/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:00:03 by mrabourd          #+#    #+#             */
/*   Updated: 2023/06/18 19:13:35 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strisalnumunderscore(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 0 && ft_isdigit(str[i]) == 0 && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

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

int	variable_already_exists(t_data *data, char *name)
{
	t_list	*check;

	check = data->env;
	while (check != NULL)
	{
		if (ft_strncmp(name, check->content, ft_strlen(name)) == 0)
			return (0);
		check = check->next;
	}
	return (1);
}

void	replace_value(t_data *data, t_list *variable, char *name)
{
	t_list	*to_replace;

	to_replace = data->env;
	while (ft_strncmp(name, to_replace->content,
			ft_strlen(to_replace->content)) != 0
		&& ft_strncmp(name, to_replace->content, ft_strlen(name)) != 0)
	{
		to_replace = to_replace->next;
	}
	free (to_replace->content);
	if (variable->next != NULL && variable->next->type == VARIABLE_VALUE)
	{
		to_replace->content = ft_strdup(name);
		to_replace->content = ft_strjoin(to_replace->content, "=");
		to_replace->content = ft_strjoin(to_replace->content,
				variable->next->content);
	}
	else
		to_replace->content = ft_strdup(variable->content);
}

int	add_variable(t_data *data, t_list *pos)
{
	t_list	*tmp;
	t_list	*new;
	int		ret;
	char	*name;

	ret = 0;
	new = NULL;
	tmp = pos;
	name = NULL;
	if (pos->next != NULL)
	{
		tmp = pos->next;
		if (ft_strchr(tmp->content, '=') != 0)
		{
			name = extract_name(data, tmp);
			if (variable_already_exists(data, name) == 0) /*name existe deja*/
				replace_value(data, tmp, name);
			else if ((tmp->content[0] == '_' || ft_isalpha(tmp->content[0]))
				&& ft_strisalnumunderscore(name))
			{
				new = ft_lstnew(tmp->content);
				new->type = ENVIRONMENT_VARIABLE;
				new->full = 0;
				if (tmp->next && tmp->next->type == VARIABLE_VALUE)
					new->content = ft_strjoin(new->content, tmp->next->content);
				ret = ft_lstadd_back(&data->env, new);
				if (ret == 1)
					exit_all(data, 1, "Problem of malloc when add a variable (export)");
			}
			free (name);
		}
	}
	return (1);
}

void	builtin_export(t_data *data, t_list *pos)
{
	if (!data->env)
		exit(EXIT_FAILURE);
	if (add_variable(data, pos) == 0)/* probleme si value est entre quotes */
		return ;
	return ;
}
