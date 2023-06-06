/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:33:03 by mrabourd          #+#    #+#             */
/*   Updated: 2023/06/06 02:34:41 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free (tab[i]);
		i++;
	}
	free (tab);
}

void	clear_cmd(t_data *data)
{
	int		i;

	i = 0;
	if (data->token_list && data->token_list != NULL)
		ft_lstclear(&data->token_list, del);
	if (data->pipes > 0)
	{
		while (i < data->pipes)
		{
			if (data->exec[i].cmd && data->exec[i].cmd != NULL)
				free_tab(data->exec[i].cmd);
			// if (data->exec[i].infile && data->exec[i].infile != NULL)
			// 	free_tab(data->exec[i].infile);
			// if (data->exec[i].outfile && data->exec[i].outfile != NULL)
			// 	free_tab(data->exec[i].outfile);
			data->exec[i].fdin = 0;
			data->exec[i].fdout = 1;
			data->exec[i].redirect_input = 0;
			data->exec[i].redirect_output = 0;
			data->exec[i].heredoc = 0;
			data->exec[i].delimiter_append = 0;
			i++;
		}
	}
}

void	exit_all(t_data *data, int err, char *str)
{
	// if (data->env && data->env != NULL)
	// {
	// 	ft_lstclear(&data->env, free);
	// }
	// if (data->token_list && data->token_list != NULL)
	// 	ft_lstclear(&data->token_list, del);
	if (data->path.tab && data->path.tab != NULL)
		free_tab(data->path.tab);
	if (data->path.line && data->path.line != NULL)
		free (data->path.line);
	if (str != NULL)
		printf("%s\n", str);
	if (err == 1)
	{
		exit(EXIT_FAILURE);
		printf("ERROR\n");
	}
	exit(EXIT_SUCCESS);
}
