/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:32:12 by mrabourd          #+#    #+#             */
/*   Updated: 2023/06/06 03:39:31 by mrabourd         ###   ########.fr       */
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
			printf("nb de redirect input: %d\n", data->exec[nb_cmd].redirect_input);
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

int	is_redirection(t_list *tmp)
{
	if (tmp->type == INFILE || tmp->type == OUTFILE
		|| tmp->type == REDIRECT_INPUT || tmp->type == REDIRECT_OUTPUT
		|| tmp->type == HEREDOC || tmp->type == ENDOFFILE)
		return (1);
	return (0);
}

void	fill_exec(t_data *data, t_list **tmp, t_exec *current, int x)
{
	int	job;
	int	y;
	t_list	*count;
	int	flag;

	y = 0;
	flag = 0;
	count = *tmp;
	job = count_cmd(count);
	init_exec(current, x);
	current[x].cmd = malloc(sizeof(char *) * (job + 1));
	if (current[x].cmd == NULL)
		exit_all(data, 1, "malloc probleme pour structure");
	while (y < job)
	{
		count_redirections(*tmp, current, x);
		if ((*tmp)->next != NULL && is_redirection(*tmp) == 1)
		{
			*tmp = (*tmp)->next;
			flag = 1;
		}
		else
		{
			current[x].cmd[y] = ft_strdup((*tmp)->content);
			printf("dup: %s\n", current[x].cmd[y]);
			y++;
		}
		if ((*tmp)->next != NULL && flag == 0)
			*tmp = (*tmp)->next;
		flag = 0;
	}
	if ((*tmp)->next != NULL && (*tmp)->type == PIPE)
		*tmp = (*tmp)->next;
	current[x].cmd[y] = NULL;
}

void	put_cmd_in_tab(t_data *data, int nb)
{
	t_list	*tmp;
	int		x;

	x = 0;
	tmp = data->token_list;
	data->exec = malloc(sizeof(t_exec) * nb);
	if (data->exec == NULL)
		exit_all(data, 1, "malloc probleme pour structure");
	while (x < nb)
	{
		fill_exec(data, &tmp, data->exec, x);
		x++;
	}
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
	put_cmd_in_tab(data, data->pipes);
	// put_redir_input_in_tab(data);
	// put_redir_output_in_tab(data);
	print_tab(data);
}
