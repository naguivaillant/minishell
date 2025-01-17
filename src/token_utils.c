/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 07:31:51 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/12 07:32:15 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	find_redir(char *str)
{
	int	i;

	i = 0;
	while (str != NULL && str[i])
	{
		if (str[i] == '<' || str[i] == '>')
			return (true);
		i++;
	}
	return (false);
}

bool	help_redirtab(char *str, int i)
{
	if (str[i] && (!separator(str[i]) || (separator(str[i] && !is_inquote(str,
						i)))))
		return (true);
	return (false);
}

void	create_redirtab_norm(char *str, int k, int count, char ***tab)
{
	int	i;
	int	j;

	i = 0;
	while (str && str[i] && k < count)
	{
		if ((str[i] == '>' || str[i] == '<') && !is_inquote(str, i))
		{
			j = i;
			i++;
			while (str[i] && str[i] == str[j])
				i++;
			if (str[i] && separator(str[i]))
			{
				while (str[i] && separator(str[i]))
					i++;
			}
			while (help_redirtab(str, i))
				i++;
			(*tab)[k++] = ft_strndup(&str[j], i - j);
		}
		if (!str[i])
			break ;
		i++;
	}
}

char	**create_redirtab(char *str)
{
	int		i;
	int		k;
	int		count;
	char	**tab;

	i = 0;
	k = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] == '>' || str[i] == '<') && !is_inquote(str, i))
		{
			count++;
			while (str[i] && (str[i] == '>' || str[i] == '<'))
				i++;
		}
		i++;
	}
	i = 0;
	tab = ft_calloc(count + 1, sizeof(char *));
	create_redirtab_norm(str, k, count, &tab);
	return (tab);
}

bool	is_redirin(char *str)
{
	if (str && str[0] == '<')
	{
		if (str[1] && str[1] != '<')
			return (true);
	}
	return (false);
}
