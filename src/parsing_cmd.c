/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:32:12 by mrabourd          #+#    #+#             */
/*   Updated: 2023/06/16 18:08:42 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_tab(t_data *data)
{
	int	i;
	int	nb_cmd;

	nb_cmd = 0;
	i = 0;
	while (nb_cmd < data->pipes)
	{
		i = 0;
		while (data->exec[nb_cmd].cmd[i])
		{
			printf("data->exec[%d].cmd[%d]: %s\n", nb_cmd, i, data->exec[nb_cmd].cmd[i]);
			i++;
		}
		nb_cmd++;
	}
}
/*
void	put_redir_output_in_tab(t_data *data)
{
	t_list	*tmp;

	tmp = data->token_list;
	while (tmp != NULL)
	{
		if (tmp->type == OUTFILE)
			data->exec.outfile = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
}

void	put_redir_input_in_tab(t_data *data)
{
	t_list	*tmp;

	tmp = data->token_list;
	while (tmp != NULL)
	{
		if (tmp->type == INFILE)
			data->exec.infile = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
}
*/
int	count_cmd(t_list *tmp)
{
	int		i;

	i = 0;
	while (tmp != NULL)
	{
		if (tmp->type != INFILE && tmp->type != OUTFILE
			&& tmp->type != REDIRECT_INPUT && tmp->type != REDIRECT_OUTPUT
			&& tmp->type != HEREDOC && tmp->type != ENDOFFILE
			&& tmp->type != PIPE)
			i++;
		if (tmp->type == PIPE)
		{
			printf("ipipe: %d\n", i);
			return (i);
		}
		tmp = tmp->next;
	}
	printf("i: %d\n", i);
	return (i);
}

void	put_cmd_in_tab(t_data *data, int nb)
{
	t_list	*tmp;
	int		x;
	int		y;
	int		job;

	x = 0;
	y = 0;
	job = 0;
	tmp = data->token_list;
	data->exec = malloc(sizeof(data->exec) * nb);
	if (data->exec == NULL)
		exit_all(data, 1, "malloc probleme pour structure");
	while (x < nb)
	{
		job = count_cmd(tmp);
		data->exec[x].cmd = malloc(sizeof(char *) * job);
		if (data->exec[x].cmd == NULL)
			exit_all(data, 1, "malloc probleme pour structure");
		y = 0;
		while (y < job)
		{
			// printf("tmp->content: %s\n", tmp->content);
			if (tmp->type != INFILE && tmp->type != OUTFILE
				&& tmp->type != REDIRECT_INPUT && tmp->type != REDIRECT_OUTPUT
				&& tmp->type != HEREDOC && tmp->type != ENDOFFILE
				&& tmp->type != PIPE)
			{
				data->exec[x].cmd[y] = ft_strdup(tmp->content);
				y++;
			}
			// printf("ok\n");
			if (tmp->next != NULL)
				tmp = tmp->next;
			else
				break ;
		}
		if (tmp->next != NULL && tmp->type == PIPE)
		{
			tmp = tmp->next;
			// printf("apres pipe: %s\n", tmp->content);
		}
		x++;
	}
}

void	count_pipes(t_data *data)
{
	t_list	*tmp;

	tmp = data->token_list;
	data->pipes = 0;
	while (tmp != NULL)
	{
		if (tmp->type == PIPE)
			data->pipes++;
		tmp = tmp->next;
	}
	data->pipes++;
}

void	parse_cmd(t_data *data)
{
	char	*str;

	str = NULL;
	str = ft_strtrim(data->input, " ");
	split_in_list(data, str);
	free (str);
	assign_type(data);
	print_all(data);
	count_pipes(data);
	printf("pipes %d\n", data->pipes);
	put_cmd_in_tab(data, data->pipes);
	// while (nb_cmd < data->pipes)
	// {
	// 	put_cmd_in_tab(data, nb_cmd);
	// 	nb_cmd++;
	// }
	// put_redir_input_in_tab(data);
	// put_redir_output_in_tab(data);
	print_tab(data);
}
