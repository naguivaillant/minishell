/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:09:50 by nassm             #+#    #+#             */
/*   Updated: 2023/10/10 14:37:12 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	normm_commande_env(char **args, int j)
{
	while (args != NULL && args[j] != NULL)
	{
		if (ft_strcmp(args[j], "env") == 0)
		{
			j++;
			continue ;
		}
		if (access(args[j], F_OK) == 0)
		{
			ft_fprintf(STDERR_FILENO, "env: %s: Premission denied\n", args[j]);
			return (126);
		}
		ft_fprintf(2, "env: %s: No such file or directory\n", args[j]);
		return (127);
		j++;
	}
	return (EXIT_SUCCESS);
}

int	norm_cmd_envbis(t_minishell *minishell, int i)
{
	while (minishell->tmp && minishell->tmp[i] != NULL)
	{
		if (ft_printf("%s\n", minishell->tmp[i]) == 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	commande_env(t_minishell *minishell, char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (minishell == NULL || minishell->env == NULL \
	|| minishell->env[0] == NULL)
		return (EXIT_FAILURE);
	if (normm_commande_env(args, j) == 127)
		return (127);
	while (minishell->env && minishell->env[i] != NULL)
	{
		if (ft_printf("%s\n", minishell->env[i]) == 0)
			return (EXIT_FAILURE);
		i++;
	}
	i = 0;
	if (minishell->tmp != NULL)
	{
		if (norm_cmd_envbis(minishell, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
