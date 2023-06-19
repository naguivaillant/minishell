/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 18:07:16 by mrabourd          #+#    #+#             */
/*   Updated: 2023/06/19 15:06:05 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_all(t_data *data)
{
	t_list	*tmp;

	tmp = data->token_list;
	printf("----START ALL-----\n");
	while (tmp != NULL)
	{
		printf("%s\n", tmp->content);
		printf("type: %u\n", tmp->type);
		// printf("%d\n", tmp->printed);
		tmp = tmp->next;
	}
	// printf("%d\n", tmp->printed);
	printf("----END ALL-----\n");
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

// void	exec_cmd(t_data *data)
// {
// 	t_list	*tmp;

// 	tmp = data->token_list;
// 	while (tmp != NULL)
// 	{
// 		if (ft_strncmp((char *)tmp->content, "export", ft_strlen(tmp->content)) == 0)
// 			builtin_export(data, tmp);
// 		if (ft_strncmp(tmp->content, "env", ft_strlen(tmp->content)) == 0)
// 			print_env(data);
// 		// if (ft_strncmp(tmp->content, "echo", ft_strlen(tmp->content)) == 0)
// 		// 	mini_echo(data);
// 		if (ft_strncmp(tmp->content, "unset", ft_strlen(tmp->content)) == 0)
// 			builtin_unset(data, tmp);
// 		tmp = tmp->next;
// 	}
// }

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	(void)argv;

	ft_bzero(&data, sizeof(data));
	if (!env || env == NULL || argc != 1)
		exit_all(&data, 1, "There is a problem with the arguments or the environment");
	fill_env_list(env, &data);
	parse_path(&data);
	while (1)
	{
		signal(SIGINT, ft_handler);
		signal(SIGQUIT, SIG_IGN);
		data.input = readline("Minishell>");
		if (!data.input)
		{
			exit_all(&data, 0, NULL);
		}
		add_history(data.input);
		parse_cmd(&data);
		pipex_heart(&data);
		clear_cmd(&data);
	}
	return (0);
}
