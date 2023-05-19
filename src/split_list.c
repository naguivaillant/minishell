/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:53:43 by mrabourd          #+#    #+#             */
/*   Updated: 2023/05/19 18:46:34 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdlib.h>
// #include <stdio.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>
// #include <readline/readline.h>
// #include <readline/history.h>
// typedef struct s_list	t_list;
// typedef struct s_data	t_data;
// void	free_tab(char **tab);
// void	exit_all(t_data *data, int err);
// int		is_metacharacter(char c);
// int		is_space(char c);
// t_list	*ft_lstnew(void *content);
// int	ft_lstadd_back(t_list **lst, t_list *new);
// void	ft_bzero(void *s, size_t n);

#include "minishell.h"

char	*fill_tmp(char *str, int len)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	if (len <= 0 || !str || str == NULL)
		return (NULL);
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp || tmp == NULL)
		return (NULL);
	while (i < len)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

void	add_node(t_data *data, char *str, int i, int j)
{
	char	*tmp;
	t_list	*new;
	int		ret;

	ret = 0;
	new = NULL;
	tmp = fill_tmp(&str[j], i - j);
	if (tmp == NULL)
		exit_all(data, 1);
	new = ft_lstnew(tmp);
	free (tmp);
	ret = ft_lstadd_back(&data->token_list, new);
	if (ret == 0)
		return ;
	if (ret != 0)
		exit_all(data, 1);
}

void	split_in_list(t_data *data, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{	
		if (j != i && (is_metacharacter(str[i]) == 1 || is_space(str[i]) == 1 || str[i] == '\"' || str[i] == '\0'))
		{
			add_node(data, str, i, j);
			while (str[i] && is_space(str[i]) == 1)
				i++;
			j = i;
		}
		if (j == i && is_space(str[i]) == 1)
		{
			while (str[i] && is_space(str[i]) == 1)
				i++;
			j = i;
		}
		if (i == j && is_metacharacter(str[i]) == 1)
		{
			i++;
			if (str[i] && str[i] == str[j])
			{
				i++;
				add_node(data, str, i, j);
				while (str[i] && is_space(str[i]) == 1)
					i++;
				if (str[i])
					j = i;
				else
					break ;
			}
			else
			{
				add_node(data, str, i, j);
			}
			while (str[i] && is_space(str[i]) == 1)
				i++;
			j = i;
			i--;
		}
		if (str[i] && i == j && str[i] == '\"')
		{
			i++;
			if (str[i])
				j = i;
			else
				break ;
			while (str[i] != '\"')
			{
				i++;
			}
			if (str[i] == '\"')
			{
				add_node(data, str, i, j);
				i++;
				if (str[i])
				{
					j = i;
					i--;
				}
				else
					break ;
			}
		}
		i++;
	}
	if (j != i && str[i] == '\0')
		add_node(data, str, i, j);
}
