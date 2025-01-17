/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:04:17 by nassm             #+#    #+#             */
/*   Updated: 2023/10/12 08:23:46 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cd_norme(void)
{
	const char	*home;

	home = getenv("HOME");
	if (home == NULL)
		return (1);
	if (chdir(home) != 0)
		return (1);
	return (0);
}

int	commande_cd(char **word)
{
	char		cwd[1000];

	if (word[2] != NULL && word[1] != NULL)
		return (ft_fprintf (2, "cd: too many arguments\n"), EXIT_FAILURE);
	if (chdir(word[1]) != 0)
	{
		if (word[1] == NULL)
		{
			if (cd_norme() == 1)
				return (EXIT_FAILURE);
			else
				return (EXIT_SUCCESS);
		}
		if (word[1][0] == '-' && !word[1][1])
			if (getcwd(cwd, sizeof(cwd)) != NULL)
				return (printf("%s\n", cwd), EXIT_SUCCESS);
		if (word [1][0] == '-' && word[1][1] == '-' && word[1][2] == '-')
			return (ft_fprintf (2, "cd: --: invalid option\n"), EXIT_FAILURE);
		if (ft_strncmp(word[1], "Makefile", 8) == 0)
			ft_fprintf(2, "cd: Makefile: Not a directory\n");
		else
			ft_fprintf(2, "cd: %s: No such file or directory\n", word[1]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
