/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:31:59 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/12 07:17:57 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	replace_str(char *cmd, char **f_result, char *var, int i)
{
	int	len;
	int	pos;
	int	j;

	len = i + 1;
	pos = 0;
	j = 0;
	while (ft_isalpha(cmd[len]) || cmd[len] == '_')
		len++;
	while (cmd[j] && j < i)
	{
		if (separator(cmd[j]))
			j = iter_separator(cmd, f_result, j, &pos);
		if (j < i)
			(*f_result)[pos++] = cmd[j++];
	}
	if (var != NULL)
	{
		while (*var)
			(*f_result)[pos++] = *var++;
	}
	replace_str_norm(&cmd, f_result, &len, &pos);
}

char	*particular_case(char **cmd, int i)
{
	int		j;
	int		k;
	char	*copy;

	j = 0;
	k = 0;
	copy = ft_calloc(ft_strlen(*cmd) + 1, sizeof(char));
	if (!copy)
		return (NULL);
	while ((*cmd)[k])
	{
		if (k != i)
			copy[j++] = (*cmd)[k++];
		else
			k++;
	}
	free(*cmd);
	*cmd = ft_strdup(copy);
	if (!cmd)
		return (NULL);
	free(copy);
	return ((*cmd));
}

void	free_envarnorm(t_env **env, char **var, char **cmd)
{
	free_tenv(*env);
	free(*var);
	free(*cmd);
}

char	*replace_envar(char **cmd, int i, t_minishell *minishell)
{
	char	*var;
	char	*to_find;
	char	*final_result;
	t_env	*env;

	env = create_env(minishell);
	if ((*cmd)[i] == '$' && !is_inquote(*cmd, i) && (*cmd)[i + 1] && ((*cmd)[i
			+ 1] == '\'' || (*cmd)[i + 1] == '\"'))
	{
		free_tenv(env);
		return (particular_case(cmd, i));
	}
	to_find = var_to_find(*cmd, i + 1);
	var = find_var(env, to_find, minishell);
	free(to_find);
	final_result = ft_calloc(ft_strlen(var) + ft_strlen(*cmd), sizeof(char));
	if (!final_result)
		return (NULL);
	replace_str(*cmd, &final_result, var, i);
	free_envarnorm(&env, &var, cmd);
	*cmd = ft_strdup(final_result);
	if (!(*cmd))
		return (NULL);
	free(final_result);
	return ((*cmd));
}

int	handle_dollar(t_token *token, t_minishell *minishell)
{
	int		i;
	char	*cmd;

	cmd = token->cmd;
	i = 0;
	while (cmd && i < (int)ft_strlen(cmd) && cmd[i])
	{
		if ((cmd[i] == '$' && !is_in_squote(cmd, i) && (ft_isalnum(cmd[i + 1])
					|| cmd[i + 1] == '?')) || (cmd[i] == '$' && !is_inquote(cmd,
					i) && ((cmd[i + 1] == '\'' || cmd[i + 1] == '\"'))))
		{
			(cmd = replace_envar(&(token->cmd), i, minishell));
			i = 0;
			continue ;
			if (cmd == NULL)
				return (-1);
		}
		i++;
	}
	return (0);
}
