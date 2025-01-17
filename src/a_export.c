/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:55:47 by nassm             #+#    #+#             */
/*   Updated: 2023/10/10 15:09:38 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	env_compare(t_minishell *data, char *arg)
{
	int		i;

	i = 0;
	if (data->env == NULL)
		data->env = ft_calloc(2, sizeof(char *));
	if (!data->env)
		return (1);
	while (data->env[i])
	{
		if (ft_strcmp(arg, data->env[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_export_arg(t_minishell *data, char *arg)
{
	if (env_compare(data, arg) != 0)
	{
		if (ft_strchr(arg, '=') != 0)
		{
			if (ft_check_lvalue(data, arg))
			{
				data->env = replace_line(data, data->env, arg);
				if (!data->env)
					free_minishell(data);
			}
			else
			{
				data->env = add_line(data->env, arg);
				if (!data->env)
					free_minishell(data);
			}
		}
	}
}

int	handle_dollar_export(char **str, t_minishell *minishell)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$' && !is_in_squote((*str), i) && \
		(ft_isalpha((*str)[i + 1]) || (*str)[i + 1] == '?'))
		{
			(*str) = replace_envar(str, i, minishell);
		}
		i++;
	}
	i = 0;
	while ((*str[i]))
	{
		if (separator((*str)[i]))
		{
			ft_fprintf(2, "ambigious redirection\n");
			return (1);
		}
	}
	return (0);
}

int	commande_export(char **arr, t_minishell *minishell)
{
	int	i;
	int	exit;

	i = 1;
	exit = 0;
	while (arr[i])
	{
		if (contain_dollar_string(arr[i]))
			exit = handle_dollar_export(&arr[i], minishell);
		if (ft_check_export_arg(arr[i]) == 1)
			exit = 1;
		else
			ft_export_arg(minishell, arr[i]);
		i++;
	}
	return (exit);
}
