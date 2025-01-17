/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_core_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:37:13 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/11 23:34:11 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_path(char **envp)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (envp[len])
		len++;
	while (i < len)
	{
		if (ft_strncmp("PATH", *envp, 4) == 0)
			return (*envp + 5);
		envp++;
		i++;
	}
	return (NULL);
}

char	**extract_path(char **envp)
{
	char	*paths;
	char	**paths_splitted;

	if (!envp || !envp[0])
		return (NULL);
	paths = find_path(envp);
	paths_splitted = ft_split(paths, ':');
	return (paths_splitted);
}

char	**split_redir(char *str)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	tab = ft_calloc(3, sizeof(char *));
	if (tab == NULL)
		return (NULL);
	while (str[i] && str[i] == str[0])
		i++;
	tab[0] = ft_strndup(str, i);
	while (str[i] && separator(str[i]))
		i++;
	j = i;
	while (str[j])
		j++;
	tab[1] = ft_strndup(&str[i], j - i);
	return (tab);
}

char	**get_command_args(char *command, int type)
{
	char	**args;
	int		i;

	i = 0;
	if (command != NULL && command[0])
	{
		if (type >= 2 && type <= 5)
			args = split_redir(command);
		else
		{
			args = ft_split_setmini(command, " \t\r\v\f");
			if (!args)
				return (NULL);
			while (args[i])
			{
				join_quote(&args[i]);
				i++;
			}
		}
		return (args);
	}
	return (NULL);
}
