/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:53:43 by mrabourd          #+#    #+#             */
/*   Updated: 2023/05/15 18:12:34 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_in_list(char *str, char c)
{
	int		i;
	int		j;
	t_list	*new;

	i = 0;
	j = 0;
	new = NULL;
	while (str[i])
	{
		if (str[i] == c)
		{
			while (str[i] != c)
			{
				new = ft_lstnew(&str[i])
			}
		}
		i++;
	}
}