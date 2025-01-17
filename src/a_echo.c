/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:16:53 by nassm             #+#    #+#             */
/*   Updated: 2023/10/10 14:18:08 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	echo_help(char *word)
{
	int	i;

	i = 2;
	while (word[i])
	{
		if (word[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	commande_echo_norm(char **word)
{
	int	i;

	i = 0;
	while (*word)
	{
		i = write(1, *word, ft_strlen(*word));
		if (i == -1)
			return (1);
		word++;
		if (*word != NULL)
			write (1, " ", 1);
	}
	return (0);
}

int	commande_echo(char **word)
{
	bool	new_line;

	new_line = true;
	if (ft_strncmp(*word, "echo", ft_strlen(*word)) != 0)
		return (EXIT_FAILURE);
	word++;
	while (*word && ft_strncmp(*word, "-n", 2) == 0)
	{
		if (echo_help(*word) == true)
		{
			new_line = false;
			word++;
		}
		else
			break ;
	}
	if (commande_echo_norm(word))
	{
		write (2, "echo: write error: No space left on device\n", 44);
		return (EXIT_FAILURE);
	}
	if (new_line)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
