/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 18:07:16 by mrabourd          #+#    #+#             */
/*   Updated: 2023/05/10 18:32:57 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_cmd(t_data *data)
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

// void	fill_cmd_list(t_data *data)
// {
// 	int		i;
// 	int		res;
// 	t_list	*new;

// 	i = 0;
// 	res = 0;
// 	while (data->cmd[i])
// 	{
// 		new = ft_lstnew(data->cmd[i]);
// 		printf("cmd %s\n", data->cmd[i]);
// 		res = ft_lstadd_back(&data->cmd_list, new);
// 		printf("data->cmd_list %s\n", (char *)data->cmd_list->content);
// 		if (res == 1)
// 			exit_all(data);
// 		i++;
// 	}
// }

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	t_data	data;

	ft_bzero(&data, sizeof(data));
	if (!env || env == NULL || argc != 1)
		exit(EXIT_FAILURE);
	while (1)
	{
		data.input = readline("Minishell>");
		add_history(data.input);
		// printf("%s", data.input);
		// printf("\n");
		parse_path(env, &data);
		fill_env_list(env, &data);
		printf("hello\n");
		data.cmd = ft_split(data.input, ' ');
		// printf("cmd %s\n", data.cmd[0]);
		// fill_cmd_list(&data);
		parse_cmd(&data);/*pour tester, mais apres faudra mieux utiliser les liste chainees je pense*/
	}
	exit_all(&data);
	return (0);
}