/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:45:29 by nassm             #+#    #+#             */
/*   Updated: 2023/10/10 15:45:35 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_get_var(t_minishell *minishell, int i)
{
	char	**split;
	char	*var;

	split = ft_split(minishell->env[i], '=');
	if (split == NULL)
		return (NULL);
	var = ft_strdup(split[0]);
	ft_free_str_array(&split);
	return (var);
}

static void	ft_del_var(t_minishell **minishell, int i)
{
	int	j;

	ft_free_str(&(*minishell)->env[i]);
	j = i;
	while ((*minishell)->env[j + 1])
	{
		(*minishell)->env[j] = (*minishell)->env[j + 1];
		j++;
		if ((*minishell)->env[j + 1] == NULL)
			(*minishell)->env[j] = NULL;
		i = ft_str_arr_len((*minishell)->env);
	}
}

static int	ft_inner_loop(char **argv, t_minishell **minishell, int i, int k)
{
	char	*var;

	var = NULL;
	if (ft_strcmp((*minishell)->env[i], argv[k]) == 0
		|| ft_strcmp((*minishell)->env[i], argv[k]) == 61)
	{
		var = ft_get_var(*minishell, i);
		if (var == NULL)
			return (EXIT_FAILURE);
		if (ft_strncmp(var, argv[k], ft_strlen(var) != 0)
			|| ft_strncmp(var, argv[k], ft_strlen(argv[k]) != 0))
		{
			ft_free_str(&var);
			return (2);
		}
		ft_del_var((minishell), i);
	}
	ft_free_str(&var);
	return (EXIT_SUCCESS);
}

int	commande_unset(char **argv, t_minishell **minishell)
{
	int		i;
	int		k;
	int		inner_out;

	k = 1;
	if (argv[k] == NULL)
		return (EXIT_SUCCESS);
	while (argv[k])
	{
		i = 0;
		while ((*minishell)->env[i])
		{
			inner_out = ft_inner_loop(argv, minishell, i, k);
			if (inner_out == 2)
				break ;
			else if (inner_out == EXIT_FAILURE)
				return (EXIT_FAILURE);
			i++;
		}
		k++;
	}
	return (EXIT_SUCCESS);
}
