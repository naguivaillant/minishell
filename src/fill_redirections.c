/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:09:31 by mrabourd          #+#    #+#             */
/*   Updated: 2023/06/18 16:54:10 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	put_redir_in_tab(t_data *data, t_list **tmp, t_exec *current)
{
	int	nb_infile;
	int	nb_outfile;

	nb_infile = 0;
	nb_outfile = 0;
	current->infile = malloc(sizeof(char *) * (current->redirect_input + 1));
	current->outfile = malloc(sizeof(char *) * (current->redirect_output + 1));
	if (current->infile == NULL || current->outfile == NULL)
		exit_all(data, 1, "problem in redirect input / output");
	while (*tmp != NULL && (*tmp)->type != PIPE)
	{
		if ((*tmp)->type == INFILE)
		{
			current->infile[nb_infile] = ft_strdup((*tmp)->content);
			nb_infile++;
		}
		if ((*tmp)->type == OUTFILE)
			current->outfile[nb_outfile++] = ft_strdup((*tmp)->content);

		*tmp = (*tmp)->next;
	}
	current->infile[current->redirect_input] = NULL;
	current->outfile[current->redirect_output] = NULL;
}

void	fill_files(t_data *data)
{
	t_list	*tmp;
	int		x;

	x = 0;
	tmp = data->token_list;
	while (x < data->pipes)
	{
		if (tmp->type == PIPE && tmp->next != NULL)
			tmp = tmp->next;
		put_redir_in_tab(data, &tmp, &data->exec[x]);
		x++;
	}
}
