/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:53:43 by mrabourd          #+#    #+#             */
/*   Updated: 2023/05/18 19:56:15 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fill_tmp(char *str, int len)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
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
	tmp = fill_tmp(&str[j], i - j);
	new = ft_lstnew(tmp);
	// printf("new: %s\n", (char *)new->content);
	free (tmp);
	ret = ft_lstadd_back(&data->token_list, new);
	if (ret == 0)
		return ;
	if (ret != 0)
		exit_all(data, 1);
}

void	remove_spaces(t_data *data)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = data->token_list;
	while (tmp != NULL)
	{
		// printf("list: %s\n", (char *)tmp->content);
		tmp->content = ft_strtrim(tmp->content, " ");
		tmp = tmp->next;
	}
}

void	split_in_list(t_data *data, char *str)
{
	int		i;
	int		j;
	int		meta;
	int		quote;

	i = 0;
	j = 0;
	meta = 0;
	quote = 0;
	while (str[i])
	{	
		if (is_space(str[i]) == 1 || is_metacharacter(str[i]) == 1 || str[i] == '\"' || str[i] == '\0')
		{
			if (meta == 0 && is_metacharacter(str[i]) == 1)
			{
				meta = 1;
				add_node(data, str, i, j);
			}
			else if (meta == 1 && is_metacharacter(str[i]) == 1)
			{
				add_node(data, str, 1, j);
				meta = 0;
			}
			else if (str[i] == '\"')
			{
				meta = 0;
				quote++;
				while (quote % 2 != 0 && str[i] != '\"')
				{
					i++;
				}
				add_node(data, str, i, j);
				i++;
			}
			else if (is_space(str[i]) == 1)
			{
				meta = 0;
				add_node(data, str, i, j);
			}
			j = i;
			if (meta == 1)
				i--;
		}
		i++;
		while (str[i] && str[i] == ' ' )
			i++;
	}
	add_node(data, str, i, j);
	j = i;
	// print_all(data);
	// remove_spaces(data);
}





// void	split_in_list(t_data *data, char *str)
// {
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{	
// 		if (is_space(str[i]) == 1 || str[i] == '\0')
// 		{
// 			add_node(data, str, i, j);
// 			i++;
// 			j = i;
// 		}
// 		else if (is_metacharacter(str[i]) == 1 || str[i] == '\0')
// 		{
// 			add_node(data, str, i, j);
// 			j = i;
// 			while (is_metacharacter(str[i]) == 1 || str[i] == '\0')
// 				i++;
// 			add_node(data, str, i, j);
// 			j = i;
// 		}
// 		else if (str[i] == '\"')
// 		{
// 			i++;
// 			while (str[i] != '\"')
// 			{
// 				if (str[i] == '\"')
// 				{
// 					add_node(data, str, i, j);
// 					j = i;
// 				}
// 				i++;
// 			}
// 		}
// 		i++;
// 		while (str[i] && str[i] == ' ' )
// 			i++;
// 	}
// 	add_node(data, str, i, j);
// 	j = i;
// 	// print_all(data);
// 	// remove_spaces(data);
// }





// void	split_in_list(t_data *data, char *str)/* a retoucher */
// {
// 	int		i;
// 	int		j;
// 	char	*tmp;
// 	t_list	*new;

// 	i = 0;
// 	j = 0;
// 	tmp = NULL;
// 	new = NULL;
// 	while (str[i])
// 	{
// 		if (is_metacharacter(str[i] == 1))
// 		{
// 			// printf("ok\n");
// 			tmp = fill_tmp(&str[j], i - j);
// 			new = ft_lstnew(tmp);
// 			ft_lstadd_back(&data->token_list, new);
// 			j = i;
// 			free (tmp);
// 			/* puis fait un node avec le metacharacter */
// 		}
// 		if (is_space(str[i]) == 1)
// 		{
// 			tmp = fill_tmp(&str[j], i - j);
// 			new = ft_lstnew(tmp);
// 			ft_lstadd_back(&data->token_list, new);
// 			j = i;
// 			free (tmp);
// 		}
// 		if (str[i] == '\"')
// 		{
// 			i++;
// 			while (str[i] != '\"')
// 			{
// 				if (str[i] == '\"')
// 				{
// 					tmp = fill_tmp(&str[j], i - j);
// 					new = ft_lstnew(tmp);
// 					ft_lstadd_back(&data->token_list, new);
// 					j = i;
// 					free (tmp);
// 				}
// 				i++;
// 			}
// 		}
// 		i++;
// 	}
// }
