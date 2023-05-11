/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:29:02 by mrabourd          #+#    #+#             */
/*   Updated: 2023/05/11 19:02:08 by mrabourd         ###   ########.fr       */
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
	char	*line;
	char	**tab;
}				t_path;

typedef struct s_data
{
	char		*input;
	char		**cmd;
	t_list		*cmd_list;
	t_list		*env;
	t_path		path;
}				t_data;

/* MAIN */
void	print_all(t_data *data);
void	fill_cmd_list(t_data *data);

/* PATH */
void	parse_path(char **env, t_data *data);

/* ENV */
void	fill_env_list(char **env, t_data *data);
int		count_list(t_list *list);
void	print_env(t_data *data);

/* EXPORT */
void	ft_sort(t_list *tmp, t_list *print);
int		builtin_export(t_data *data);

/* ECHO */
void	print_lines(int i, char **str, int fd);
int		mini_echo(t_data *cmd);

/* EXIT */
void	free_tab(char **tab);
void	exit_all(t_data *data);

#endif