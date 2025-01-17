/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:41:19 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/11 20:41:21 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	contain_dollar(t_token *token)
{
	if (ft_strchr(token->cmd, '$') != NULL)
		return (true);
	return (false);
}

char	*var_to_find(char *cmd, int i)
{
	char	*to_find;
	int		len;

	to_find = NULL;
	len = i;
	if (cmd[len - 1] == '$' && len < (int)ft_strlen(cmd) && cmd[len] == '?')
		len++;
	else
	{
		while (cmd[len] && (ft_isalnum(cmd[len])))
			len++;
	}
	to_find = ft_strndup(&cmd[i], len - i);
	if (!to_find)
		return (NULL);
	if (ft_strlen(to_find) == 0)
	{
		free(to_find);
		return (NULL);
	}
	return (to_find);
}

char	*find_var(t_env *env, char *to_find, t_minishell *minishell)
{
	char	*var;

	var = NULL;
	if (to_find == NULL)
		return (NULL);
	if (ft_strcmp(to_find, "?") == 0)
		return (ft_itoa(minishell->exit_code));
	while (env)
	{
		if (ft_strcmp(env->key, to_find) == 0)
		{
			var = ft_strdup(env->value);
			break ;
		}
		env = env->next;
	}
	return (var);
}

int	iter_separator(char *cmd, char **f_result, int j, int *pos)
{
	(*f_result)[(*pos)++] = ' ';
	j++;
	while (cmd[j] && separator(cmd[j]))
		j++;
	return (j);
}
