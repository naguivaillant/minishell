/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:13:01 by nassm             #+#    #+#             */
/*   Updated: 2023/08/30 16:46:38 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	commande_pwd(void)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (cwd == NULL)
	{
		perror("Error");
		return (EXIT_FAILURE);
	}
	else if (ft_printf("%s\n", cwd) != (int)ft_strlen(cwd) + 1)
	{
		ft_free_str(&cwd);
		perror("\nError: printf failed");
		return (EXIT_FAILURE);
	}
	ft_free_str(&cwd);
	return (EXIT_SUCCESS);
}
