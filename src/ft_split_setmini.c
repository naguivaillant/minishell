/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_setmini.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 18:14:36 by nassm             #+#    #+#             */
/*   Updated: 2023/10/11 20:20:43 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	get_arr_len(char *str, char *set)
{
	char	*trimmed_str;
	int		arr_len;
	int		i;

	trimmed_str = ft_strtrim(str, set);
	if (trimmed_str == NULL)
		return (-1);
	arr_len = 0;
	i = 0;
	if (ft_strchr(set, trimmed_str[i]) == NULL)
		arr_len++;
	while (trimmed_str[i])
	{
		if (ft_strchr(set, trimmed_str[i]) != NULL)
			arr_len++;
		i++;
	}
	free(trimmed_str);
	return (arr_len);
}

static size_t	get_size(char *str, char *set)
{
	size_t	size;
	int		i;

	size = 0;
	i = 0;
	while (str[i] && (ft_strchr(set, str[i]) == NULL || (ft_strchr(set,
					str[i]) != NULL && is_inquote(str, i))))
	{
		size++;
		i++;
	}
	return (size);
}

void	ft_split_semininorm(char *str, char *set, int i, char ***arr)
{
	bool	inside_quotes;
	int		arr_len;
	int		j;

	inside_quotes = false;
	arr_len = get_arr_len(str, set);
	while (i < arr_len && *str)
	{
		while (*str && ft_strchr(set, *str) != NULL)
			str++;
		(*arr)[i] = ft_calloc(get_size(str, set) + 1, sizeof((**arr)[i]));
		if ((*arr)[i] == NULL)
			(ft_free_split(*arr));
		j = 0;
		while (*str && (ft_strchr(set, *str) == NULL || inside_quotes))
		{
			if (*str == '\'' || *str == '"')
				inside_quotes = !inside_quotes;
			(*arr)[i][j++] = *str++;
		}
		i++;
	}
}

char	**ft_split_setmini(char *str, char *set)
{
	char	**arr;
	int		arr_len;
	int		i;
	bool	inside_quotes;

	inside_quotes = false;
	if (str == NULL || set == NULL)
		return (NULL);
	arr_len = get_arr_len(str, set);
	arr = ft_calloc(arr_len + 1, sizeof(*arr));
	if (arr == NULL)
		return (NULL);
	i = 0;
	ft_split_semininorm(str, set, i, &arr);
	return (arr);
}
