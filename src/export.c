/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:00:03 by mrabourd          #+#    #+#             */
/*   Updated: 2023/05/27 12:17:03 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

	/* --- Mark each name to be passed to child processes in the environment. The names
refer to shell variables*/
	/*If no names are supplied, a list of names of all exported variables is displayed.*/
	/*If a variable name is followed by =value, the value of the variable is set to value.*/
	/*The return status is zero unless 
one of the names is not a valid shell variable name. --- */

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
	print->printed = 1;
	printf("declare -x %s\n", (char *)print->content);
}

void	back_to_zero(t_data *data)
{
	t_list	*tmp;

	tmp = data->env;
	while (tmp != NULL)
	{
		tmp->full = 0;
		tmp->printed = 0;
		// tmp->type = 0;
		tmp = tmp->next;
	}
}

int	add_variable(t_data *data, t_list *pos)
{
	t_list	*tmp;
	t_list	*new;

	new = NULL;
	tmp = pos;
	if (pos->next != NULL)
	{
		tmp = pos->next;
		if (ft_strchr(tmp->content, '=') != 0)
		{
			new = ft_lstnew(tmp->content);
			// printf("new next: %s\n", (char *)new->content);
			ft_lstadd_back(&data->env, new);
			// print_all(data);
			print_env(data);
			return (0);
		}
		// else if (tmp && tmp->type != 3)/* ----- changer ici -- pour dire que si c'est une variable sans value, 
		// 									faut quand meme l'afficher dans export mais pas dans env*/
		// {
		// 	// print_all(data);
		// 	data->env->full = 1;
		// 	return (0);
		// }
	}
	// printf("tmp debut: %s\n", (char *)tmp->content);
	// while (tmp->next != NULL)/* ------------- probleme ici, n'affiche pas la bonne commande */
	// {
	// 	if (tmp->next != NULL && ft_strncmp((char *)tmp->content, "export", ft_strlen(tmp->content)) == 0)
	// 	{
	// 		tmp = tmp->next;
	// 		// printf("tmp next: %s\n", (char *)tmp->content);
	// 		if (ft_strchr(tmp->content, '=') != 0)
	// 		{
	// 			new = ft_lstnew(tmp->content);
	// 			printf("new next: %s\n", (char *)new->content);
	// 			ft_lstadd_back(&data->env, new);
	// 			// print_all(data);
	// 			return (0);
	// 		}
	// 		else if (tmp && tmp->type != 3)/* ----- changer ici -- pour dire que si c'est une variable sans value, 
	// 											faut quand meme l'afficher dans export mais pas dans env*/
	// 		{
	// 			// print_all(data);
	// 			data->env->full = 1;
	// 			return (0);
	// 		}
	// 	}
	// 	tmp = tmp->next;
	// }
	return (1);
}

int	builtin_export(t_data *data, t_list *pos)
{
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
	if (add_variable(data, pos) == 0)
		return (0);
	count = count_list(data->env);
	printf("count: %d\n", count);
	tmp = data->env;
	while (i < count)
	{
		print = data->env;
		tmp = data->env;
		ft_sort(tmp, print);
		i++;
	}
	back_to_zero(data);
	return (0);
}
