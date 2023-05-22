/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 18:07:16 by mrabourd          #+#    #+#             */
/*   Updated: 2023/05/22 18:06:55 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_all(t_data *data)
{
	t_list	*tmp;

	tmp = data->token_list;
	printf("----START ALL-----\n");
	while (tmp != NULL)
	{
		printf("%s\n", tmp->content);
		// printf("type: %u\n", tmp->type);
		// printf("%d\n", tmp->printed);
		tmp = tmp->next;
	}
	// printf("%d\n", tmp->printed);
	printf("----END ALL-----\n");
}

void	exec_cmd(t_data *data)
{
	t_list	*tmp;

	tmp = data->token_list;
	while (tmp != NULL)
	{
		// if (ft_strncmp((char *)tmp->content, "export", ft_strlen(tmp->content)) == 0)
		// 	builtin_export(data, tmp);
		if (ft_strncmp((char *)tmp->content, "env", ft_strlen(tmp->content)) == 0)
			print_env(data);
		if (ft_strncmp((char *)tmp->content, "echo", ft_strlen(tmp->content)) == 0)
			mini_echo(data);
		if (ft_strncmp((char *)tmp->content, "unset", ft_strlen(tmp->content)) == 0)
			builtin_unset(data);
		tmp = tmp->next;
	}
}

void	ft_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	(void)argv;

	ft_bzero(&data, sizeof(data));
	ft_bzero(&data.token_list, sizeof(data.token_list));
	ft_bzero(&data.env, sizeof(data.env));
	// printf("&data.env %s\n", (char *)&data.env->content);
	if (!env || env == NULL || argc != 1)
		exit_all(&data, 1);
	parse_path(env, &data);
	// fill_env_list(env, &data);
	while (1)
	{
		signal(SIGINT, ft_handler);
		signal(SIGQUIT, SIG_IGN);
		data.input = readline("Minishell>");
		if (!data.input)
		{
			exit_all(&data, 0);
		}
		add_history(data.input);
		parse_cmd(&data);
	//	execution(&data);a faire
	}
	return (0);
}

/*
OLD :
		data.input = readline("Minishell>");
		add_history(data.input);
		// data.cmd = ft_split(data.input, ' ');  -> old one
		parse_cmd(&data);
		// fill_token_list(&data);
		exec_cmd(&data);
		ft_lstclear(&data.token_list, free);

*/