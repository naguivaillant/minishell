/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:29:02 by mrabourd          #+#    #+#             */
/*   Updated: 2023/06/12 16:02:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "../libft/libft.h"

typedef struct s_path
{
	char	*line;
	char	**tab;
}				t_path;

typedef	struct s_here
{
	char	*delim;
	int		pipe[2];
}				t_here;


typedef struct	s_exec
{
	int			pipes;
	char		**cmd;
	char		*cmd_state;
	char		*infile;
	char		*outfile;
	int			fdin;
	int			fdout;
	int			here_nb;
	int			*pipefd;
	int			prev_pipe;
	char		*strerror;
	char		**av;
	int			err;
	int			*pid;
	int			index;
	int			nbcmd;
	int			status;
	t_here		*here;
	t_path		*path;
}				t_exec;

typedef struct s_data
{
	char		*input;
	t_exec		exec;
	t_list		*token_list;
	t_list		*env;
	t_path		path;
}				t_data;

/* MAIN */
void	print_all(t_data *data);

/* PARSE COMMANDES */
void	assign_type(t_data *data);
void	parse_cmd(t_data *data);

/* SPLIT LIST */
int		is_metacharacter(char c);
int		is_space(char c);
char	*fill_tmp(char *str, int len);
void	add_node(t_data *data, char *str, int i, int j);
void	add_node_quote(t_data *data, char *str, int i, int j);
void	split_in_list(t_data *data, char *str);

/* PATH */
void	parse_path(char **env, t_data *data);

/* ENV */
void	fill_env_list(char **env, t_data *data);
int		count_list(t_list *list);
void	print_env(t_data *data);

/* EXPORT */
void	ft_sort(t_list *tmp, t_list *print);
int		builtin_export(t_data *data, t_list *pos);

/* ECHO */
// void	print_lines(int i, char **str, int fd);
// int		mini_echo(t_data *cmd);

/* UNSET */
void	builtin_unset(t_data *data);

/*EXEC */
int	exec_solo_built(t_list *env, t_data *data);
int	exec(t_list *env, t_exec *exec, int i);
int	is_a_built(t_list *env, t_exec *exec);
int	pipex_heart(t_list *env, t_exec *exec);
void	child_process(t_exec *exec, t_list *env, int i);
void	waitin(t_exec *exec);
void	parent_process(t_exec *exec);
int	pipex(char *read, t_list *env);
int	struct_init(t_exec *exec, t_list *env, char *read);
void	free_tab(char **tab);
char	**get_cmd_path(t_exec *exec);
char	*cmd_final_state(t_exec *exec, char *cmd);
int	heredoc_count(char **tab);
void	dup_n_close(int oldfd, int newfd);
int	isaredirection(char *str);
void	redir_finder(t_exec *exec, t_list *env, char **cmd, int toggle);
int	builtins_finder(char **cmd);
void	exec_builtins(char **cmd, t_exec *exec, t_list *env, int toggle);

/* EXIT */
void	clear_cmd(t_data *data);
void	free_tab(char **tab);
void	exit_all(t_data *data, int err, char *str);

#endif
