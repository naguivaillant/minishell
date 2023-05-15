/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 18:07:16 by mrabourd          #+#    #+#             */
/*   Updated: 2023/05/15 16:41:17 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	exec_str_cmd(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->cmd[i])
	{
		if (data->cmd[i][j] == 'e')
		{
			j++;
			if (data->cmd[i][j] == 'n')
			{
				j++;
				if (data->cmd[i][j] == 'v')
				{
					print_env(data);
					return ;
				}
			}
			else if (data->cmd[i][j] == 'c')
			{
				j++;
				if (data->cmd[i][j] == 'h')
				{
					j++;
					if (data->cmd[i][j] == 'o')
					{
						mini_echo(data);
						return ;
					}
				}
			}
			else if (data->cmd[i][j] == 'x')
			{
				j++;
				if (data->cmd[i][j] == 'p')
				{
					j++;
					if (data->cmd[i][j] == 'o')
					{
						builtin_export(data);
						return ;
					}
				}
			}
		}
	}
}
*/
void	print_all(t_data *data)
{
	t_list	*tmp;

	tmp = data->env;
	printf("----START ALL-----\n");
	while (tmp != NULL)
	{
		printf("%s\n", (char *)tmp->content);
		// printf("%d\n", tmp->printed);
		tmp = tmp->next;
	}
	// printf("%d\n", tmp->printed);
	printf("----END ALL-----\n");
}

void	fill_cmd_list(t_data *data)
{
	int		i;
	int		res;
	t_list	*new;

	i = 0;
	res = 0;
	new = NULL;
	while (data->cmd[i])
	{
		new = ft_lstnew(data->cmd[i]);
		res = ft_lstadd_back(&data->cmd_list, new);
		if (res == 1)
			exit_all(data);
		i++;
	}
	// print_all(data);
}

void	exec_cmd(t_data *data)
{
	t_list	*tmp;

	tmp = data->cmd_list;
	while (tmp != NULL)
	{
		if (ft_strncmp((char *)tmp->content, "export", ft_strlen(tmp->content)) == 0)
			builtin_export(data, tmp);
		if (ft_strncmp((char *)tmp->content, "env", ft_strlen(tmp->content)) == 0)
			print_env(data);
		if (ft_strncmp((char *)tmp->content, "echo", ft_strlen(tmp->content)) == 0)
			mini_echo(data);
		if (ft_strncmp((char *)tmp->content, "unset", ft_strlen(tmp->content)) == 0)
			builtin_unset(data);
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	(void)argv;

	ft_bzero(&data, sizeof(data));
	ft_bzero(&data.cmd_list, sizeof(data.cmd_list));
	ft_bzero(&data.env, sizeof(data.env));
	// printf("&data.env %s\n", (char *)&data.env->content);
	if (!env || env == NULL || argc != 1)
		exit(EXIT_FAILURE);
	parse_path(env, &data);
	fill_env_list(env, &data);
	while (1)
	{
		data.input = readline("Minishell>");
		add_history(data.input);
		// data.cmd = ft_split(data.input, ' ');/*old one*/
		parse_cmd(&data);
		// fill_cmd_list(&data);
		exec_cmd(&data);
		// exec_str_cmd(&data);/*pourtester mais faudra utiliser la listechainee*/
		ft_lstclear(&data.cmd_list, free);
	}
	exit_all(&data);
	return (0);
}
