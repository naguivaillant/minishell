/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:00:03 by mrabourd          #+#    #+#             */
/*   Updated: 2023/05/10 16:05:00 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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

// void	add_variable(t_data *data)
// {
// 	int	i;
// 	int	y;

// 	i = 0;
// 	y = 0;
// 	if ()
// }

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
	// add_variable(data);/* <--- a faire, pour ajouter 'VARIABLE=value' le cas echeant dans 'env'*/
	return (0);
}