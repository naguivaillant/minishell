/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_export_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:27:55 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/10 15:40:14 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*remove_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '+')
		i++;
	str[i] = '\0';
	return (str);
}

int	ft_freetab(char **tab, int boolean)
{
	int	i;

	i = 0;
	if (!tab || !tab[0])
		return (1);
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	if (boolean)
		return (0);
	ft_printf("Error\n");
	exit(1);
}

char	*ft_lvalue(t_minishell *data, char *arg)
{
	int		i;
	char	*temp;

	(void) data;
	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	temp = ft_calloc(i + 1, sizeof(char));
	if (!temp)
	{
		return (NULL);
		free_minishell(data);
	}
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		temp[i] = arg[i];
		i++;
	}
	temp[i] = '\0';
	if (check_value_add(temp))
		temp = remove_plus(temp);
	return (temp);
}

int	ft_check_lvalue(t_minishell *data, char *arg)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_lvalue(data, arg);
	if (check_value_add(temp))
		temp = remove_plus(temp);
	while (data->env[i])
	{
		if (ft_strncmp(temp, data->env[i], ft_strlen(temp)) == 0)
		{
			free(temp);
			return (1);
		}
		i++;
	}
	free (temp);
	return (0);
}

char	**replace_line(t_minishell *data, char **env, char *new)
{
	char	*temp;
	int		i;

	i = 0;
	temp = ft_lvalue(data, new);
	if (!contain_plusequal(new))
	{
		while (env[i])
		{
			if (ft_strncmp(temp, env[i], ft_strlen(temp)) == 0)
			{
				ft_free_str(&env[i]);
				env[i] = ft_strdup(new);
			}
			i++;
		}
	}
	else
		join_value(&env, temp, new);
	free(temp);
	return (env);
}
