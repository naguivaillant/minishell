/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:29:02 by mrabourd          #+#    #+#             */
/*   Updated: 2023/05/02 18:21:18 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_path
{
	char *line;
	char **tab;
}				t_path;

typedef struct s_data
{
	char	*input;
	char	**cmd;
	t_list	*env;
	t_path	path;
}				t_data;

/* MAIN */

/* PATH */
void	parse_path(char **env, t_data *data);
void	builtin_env(char **env, t_data *data);

/* EXIT */
void	exit_all(t_data *data);

#endif