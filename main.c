/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 18:07:16 by mrabourd          #+#    #+#             */
/*   Updated: 2023/05/04 15:09:53 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		printf("%s", data.input);
		printf("\n");
		parse_path(env, &data);
		fill_env_list(env, &data);
		data.cmd = ft_split(data.input, ' ');
		if (data.cmd[0][0] == 'e')
			print_env(&data);
		if (data.cmd[0][0] == 'x')
			builtin_export(&data);
	}
	exit_all(&data);
	return (0);
}