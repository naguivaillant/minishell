/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:05:25 by mrabourd          #+#    #+#             */
/*   Updated: 2023/05/04 19:09:51 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_path(char **env, t_data *data)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			data->path.line = ft_strdup(&env[i][5]);
		i++;
	}
	if (env)
		data->path.tab = ft_split(data->path.line, ':');
}

void	fill_env_list(char **env, t_data *data)
{
	int	i;
	int	res;
	t_list	*new;

	i = 0;
	res = 0;
	while (env[i])
	{
		new = ft_lstnew(env[i]);
		res = ft_lstadd_back(&data->env, new);
		if (res == 1)
			exit_all(data);
		i++;
	}
}

int	count_list(t_list *list)
{
	t_list *tmp;
	int		i;

	tmp = list;
	i = 0;
	while (tmp->next != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	print_env(t_data *data)
{
	int count = count_list(data->env);
	printf("count %d\n", count);
	while (data->env)
	{
		printf("%s\n", (char *)data->env->content);
		data->env = data->env->next;
	}
}
/*
void	print_all(t_data *data)
{
	t_list *tmp;
	// int		y;

	// y = 0;
	tmp = data->env;
	printf("----START ALL-----\n");
	while (tmp->next != NULL)
	{
		// printf("%s\n", (char *)tmp->content);
		printf("%d\n", tmp->printed);
		tmp = tmp->next;
		// y++;
	}
	printf("%d\n", tmp->printed);
	printf("----END ALL-----\n");
}
*/
void	ft_sort(t_list *tmp, t_list *print)
{
	while (print->next && print->printed == 1)
		print = print->next;
	while (tmp && tmp->next != NULL)
	{
		if (ft_strncmp(print->content, tmp->content, ft_strlen(tmp->content)) < 0)
			tmp = tmp->next;
		if (ft_strncmp(print->content, tmp->content, ft_strlen(tmp->content)) >= 0)
		{
			if (tmp->printed == 0)
				print = tmp;
			tmp = tmp->next;
		}
	}
	printf("declare -x %s\n", (char *)print->content);
	print->printed = 1;
}

int	builtin_export(t_data *data)
{
	/* --- Mark each name to be passed to child processes in the environment. The names
refer to shell variables*/
	/*If no names are supplied, a list of names of all exported variables is displayed.*/
	/*If a variable name is followed by =value, the value of the variable is set to value.*/
	/*The return status is zero unless 
one of the names is not a valid shell variable name. --- */
	
	t_list	*tmp;
	t_list	*print;
	int		count;
	int		i;

	tmp = NULL;
	print = NULL;
	count = 0;
	i = 0;
	if (!data->env)
		exit(EXIT_FAILURE);
	print = data->env;
	tmp = data->env;
	count = count_list(print);
	while (i < count)
	{
		print = data->env;
		tmp = data->env;
		ft_sort(tmp, print);
		i++;
	}
	add_variable(data);/* <--- a faire, pour ajouter 'VARIABLE=value' le cas echeant dans 'env'*/
	return (0);
}