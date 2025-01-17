/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_export_2utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:06:38 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/12 01:30:36 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_export_arg(char *str)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (str[i] != '_' && ft_isalpha(str[i]) == 0)
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("' : not a valid identifier\n", 2);
		return (1);
	}
	i++;
	while (str[i] && str[i] != '=')
	{
		if (str[i] != '_' && ft_isalnum(str[i]) == 0 && str[i] != '+')
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("' : not a valid identifier\n", 2);
			return (1);
		}
		i++;
	}
	return (ret);
}

int	add_linenorm(char **env, char **new_line, int *i)
{
	while (env[*i])
	{
		new_line[*i] = ft_strdup(env[*i]);
		if (!new_line[*i])
		{
			ft_free_tab(new_line);
			return (EXIT_FAILURE);
		}
		(*i)++;
	}
	return (EXIT_SUCCESS);
}

char	**add_line(char **env, char *new)
{
	int		i;
	char	**new_line;

	i = 0;
	while (env[i])
			i++;
	new_line = malloc(sizeof(char *) * (i + 2));
	if (!new_line)
		return (NULL);
	i = 0;
	if (add_linenorm(env, new_line, &i) == EXIT_FAILURE)
		return (NULL);
	new_line[i] = ft_strdup(new);
	if (!new_line[i])
	{
		ft_free_tab(new_line);
		return (NULL);
	}
	i++;
	new_line[i] = NULL;
	ft_freetab(env, 1);
	return (new_line);
}

bool	check_value_add(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && ft_isalnum(str[i - 1]))
			return (true);
		i++;
	}
	return (false);
}
