/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:32:12 by mrabourd          #+#    #+#             */
/*   Updated: 2023/06/01 16:43:04 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_tab(t_data *data)
{
	int	i;

	i = 0;
	while (data->exec.cmd[i])
	{
		printf("cmd tab: %s\n", data->exec.cmd[i]);
		i++;
	}
}

// void	put_redir_output_in_tab(t_data *data)
// {
// 	t_list	*tmp;
// 	int		y;

// 	tmp = data->token_list;
// 	while (tmp != NULL)
// 	{
// 		y = 0;
// 		if (tmp->type == REDIRECT_OUTPUT)
// 		{
// 			data->redirections[1][y] = *tmp->content;
// 			y++;
// 			tmp = tmp->next;
// 		}
// 		if (tmp->type == OUTFILE)
// 		{
// 			data->redirections[1][y] = *tmp->content;
// 			y++;
// 			tmp = tmp->next;
// 		}
// 		tmp = tmp->next;
// 	}
// 	data->redirections[1][y] = '\0';
// }

// void	put_redir_input_in_tab(t_data *data)
// {
// 	t_list	*tmp;
// 	int		y;

// 	tmp = data->token_list;
// 	while (tmp != NULL)
// 	{
// 		y = 0;
// 		if (tmp->type == REDIRECT_INPUT)
// 		{
// 			data->redirections[0][y] = *tmp->content;
// 			y++;
// 			tmp = tmp->next;
// 		}
// 		if (tmp->type == INFILE)
// 		{
// 			data->redirections[0][y] = *tmp->content;
// 			y++;
// 			tmp = tmp->next;
// 		}
// 		tmp = tmp->next;
// 	}
// 	data->redirections[0][y] = '\0';
// }

int		count_cmd(t_data *data)
{
	int		i;
	t_list	*tmp;
	
	i = 0;
	tmp = data->token_list;
	while (tmp != NULL)
	{
		if (tmp->type != INFILE && tmp->type != OUTFILE
			&& tmp->type != REDIRECT_INPUT && tmp->type != REDIRECT_OUTPUT
			&& tmp->type != OUTFILE && tmp->type != HEREDOC 
			&& tmp->type != ENDOFFILE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	put_cmd_in_tab(t_data *data)
{
	t_list	*tmp;
	int		i;
	int		tab;

	i = 0;
	tmp = data->token_list;
	tab = count_cmd(data);
	if (tab < 1)
		exit_all(data, 1, "There is no command");
	data->exec.cmd = malloc(sizeof(char *) * (tab + 1));
	if (data->exec.cmd == NULL || !data->exec.cmd)
		exit_all(data, 1, "probleme de malloc sur la tab de cmd");
	while (tmp != NULL)
	{
		if (tmp->type != INFILE && tmp->type != OUTFILE
			&& tmp->type != REDIRECT_INPUT && tmp->type != REDIRECT_OUTPUT
			&& tmp->type != OUTFILE && tmp->type != HEREDOC 
			&& tmp->type != ENDOFFILE && i <= tab)
		{
			data->exec.cmd[i] = ft_strdup(tmp->content);
			i++;
		}
		tmp = tmp->next;
	}
	data->exec.cmd[i] = NULL;
}

void	count_pipes(t_data *data)
{
	t_list	*tmp;

	tmp = data->token_list;
	while (tmp != NULL)
	{
		if (tmp->type == PIPE)
			data->exec.pipes++;
		tmp = tmp->next;
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
	printf("pipes %d\n", data->exec.pipes);
	// put_redir_input_in_tab(data);
	// put_redir_output_in_tab(data);
	put_cmd_in_tab(data);
	print_tab(data);
}
