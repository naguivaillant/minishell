/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:32:12 by mrabourd          #+#    #+#             */
/*   Updated: 2023/05/31 17:02:37 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_tab(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmd[i])
	{
		printf("cmd tab: %s\n", data->cmd[i]);
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

	tmp = data->token_list;
	i = count_cmd(data);
	data->cmd = malloc(sizeof(char *) * i);
	if (data->cmd == NULL)
		exit_all(data, 1, "probleme de malloc sur la tab de cmd");
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->type != INFILE && tmp->type != OUTFILE
			&& tmp->type != REDIRECT_INPUT && tmp->type != REDIRECT_OUTPUT
			&& tmp->type != OUTFILE && tmp->type != HEREDOC 
			&& tmp->type != ENDOFFILE)
		{
			data->cmd[i] = ft_strdup(tmp->content);
			i++;
		}
		tmp = tmp->next;
	}
	data->cmd[i] = NULL;
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
	// put_redir_input_in_tab(data);
	// put_redir_output_in_tab(data);
	put_cmd_in_tab(data);
	print_tab(data);
}