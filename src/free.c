/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:53:53 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/11 19:57:10 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_token(t_token **token)
{
	t_token	*tmp;

	while (*token != NULL)
	{
		tmp = (*token)->next_token;
		if ((*token)->cmd != NULL)
			free((*token)->cmd);
		(*token)->cmd = NULL;
		if ((*token)->args)
			ft_free_tab((*token)->args);
		if ((*token)->redirin)
			ft_free_tab((*token)->redirin);
		if ((*token)->redirout)
			ft_free_tab((*token)->redirout);
		if ((*token)->here_doc != NULL)
			ft_free_tab((*token)->here_doc);
		(*token)->args = NULL;
		free(*token);
		*token = tmp;
	}
}

void	free_exec(t_exec *exec)
{
	t_exec	*tmp;

	while (exec != NULL)
	{
		tmp = exec->next;
		if (exec->cmd != NULL)
			free(exec->cmd);
		exec->cmd = NULL;
		if (exec->args != NULL)
		{
			ft_free_tab(exec->args);
			exec->args = NULL;
		}
		if (exec->paths != NULL)
			ft_free_tab(exec->paths);
		if (exec->outfile != NULL)
			ft_free_tab(exec->outfile);
		if (exec->infile != NULL)
			ft_free_tab(exec->infile);
		if (exec->here_doc != NULL)
			ft_free_tab(exec->here_doc);
		free(exec);
		exec = tmp;
	}
	free (exec);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_minishell(t_minishell *minishell)
{
	if (minishell->env)
		ft_free_tab(minishell->env);
	if (minishell->tmp)
		ft_free_tab(minishell->tmp);
	free(minishell);
}

void	free_tenv(t_env *env)
{
	t_env	*tmp;

	while (env != NULL)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}
