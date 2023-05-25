/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:29:02 by mrabourd          #+#    #+#             */
/*   Updated: 2023/05/21 16:26:56 by mrabourd         ###   ########.fr       */
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
# include <signal.h>
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
	t_path		path;
}				t_data;

typedef struct s_token					//pour definir le type
{
	char	*str;
	int		type;
}	t_token;

typedef struct s_command				//ma gestion du parsing de commandes
{
	char	*fdin;
	char	*fdout;
	int		ofdout;
	int		ofdin;
	char	*error;
	char	**cmd;
	char	*file;
	int		type;
}	t_command;


typedef struct s_pos
{
	struct s_list	*start;				//pour acceder a la liste chainee
	int				*size;
}	t_pos;

typedef struct s_list
{
	struct s_list	*next;				//liste double chainee apres
	struct s_list	*back;				//liste doucle chainee avant
	void			*content;
	struct s_pos	*pos;				//pour acceder aux postiions ou on est
}	t_list;

typedef struct s_minishell
{
	t_pos		*garbage;			//pour acceder a l'input
	t_pos		*garbagecmd;			//pour acceder a l'input quand c'est une commande
	int			heredoc;		//utils du heredoc
	int			heredocprompt;		//tout pareil
	char		**argv;
	int			argc;
	int			*pipe;			//pour stocker les pipes
	char		*error;				//pour print les erreurs plus simplement
	t_pos		*tokenlist;			//pour definir le type
	int			laststatus;		//pour le signal
	int			fdutil;			//pour les redirections
}	t_minishell;

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
void	print_lines(int i, char **str, int fd);
int		mini_echo(t_data *cmd);

/* UNSET */
void	builtin_unset(t_data *data);

/* EXIT */
void	free_tab(char **tab);
void	exit_all(t_data *data, int err);

#endif

