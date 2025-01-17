/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollars_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 07:18:17 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/12 07:20:39 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	replace_str_norm2(char **f_result, int *pos, char **tmp, int i)
{
	(*f_result)[(*pos)] = '\0';
	if (i != (int)ft_strlen(*tmp))
		*f_result = ft_strjoin(*f_result, tmp[i]);
	free(*tmp);
	return ;
}

void	replace_str_norm(char **cmd, char **f_result, int *len, int *pos)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(*cmd);
	while (tmp[i] && tmp[i] != '$')
		i++;
	i++;
	while (tmp[i] && (ft_isalpha(tmp[i]) || tmp[i] == '_'))
		i++;
	if ((*pos) > 0 && (*f_result)[(*pos) - 1] == ' ')
		return (replace_str_norm2(f_result, pos, &tmp, i));
	if (*len < (int)ft_strlen(*cmd) && (*cmd)[*len] == '?'
		&& ft_isdigit((*f_result)[(*pos - 1)]))
		(*len)++;
	while (*len < (int)ft_strlen(*cmd) && (*cmd)[*len] && *len != 0)
	{
		if (separator((*cmd)[*len]))
			*len = iter_separator((*cmd), f_result, *len, pos);
		(*f_result)[(*pos)++] = (*cmd)[(*len)++];
	}
	(*f_result)[(*pos)] = '\0';
	free(tmp);
}

bool	all_digit(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}
