/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:00:38 by nassm             #+#    #+#             */
/*   Updated: 2023/10/10 14:44:48 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_no_number(char *tab)
{
	int	i;

	i = 0;
	if (tab[0] == '-' && (tab[1] >= '0' || tab[1] <= '9'))
		i++;
	if (tab[0] == '+' && (tab[1] >= '0' || tab[1] <= '9'))
		i++;
	while (tab[i])
	{
		if (tab[i] < '0' || tab[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

void	print_error_arg(void)
{
	ft_fprintf(STDERR_FILENO, "exit\n");
	ft_fprintf(STDERR_FILENO, "exit: too many arguments\n");
}

void	exit_nbarg(t_minishell *minishell, t_exec *exec, char *str)
{
	ft_fprintf(STDERR_FILENO,
		"exit: %s: numeric argument required\n", str);
	free_exec(exec);
	free_minishell(minishell);
	exit (2);
}

int	commande_exit(char **tab, t_minishell *minishell,
		t_exec *exec, t_exec *head)
{
	int	exitc;

	exitc = minishell->exit_code;
	if (ft_strncmp(tab[0], "exit", ft_strlen(tab[0])) != 0)
		return (EXIT_FAILURE);
	if (tab[1] != NULL)
	{
		if (check_no_number(tab[1]) == 1 || ft_strlen(tab[1]) > 19)
			exit_nbarg(minishell, exec, tab[1]);
		else
		{
			if (tab[2] != NULL)
				return (print_error_arg(), EXIT_FAILURE);
			ft_fprintf(STDERR_FILENO, "exit\n");
		}
	}
	else
		ft_fprintf(STDERR_FILENO, "exit\n");
	free_minishell(minishell);
	if (exec->args[1] != NULL)
		exitc = ft_atoi(exec->args[1]);
	if (head != NULL)
		free_exec(head);
	exit(exitc);
}
