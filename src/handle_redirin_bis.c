/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirin_bis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 07:25:37 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/12 07:27:36 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_redirouts(char *str, t_exec **exec)
{
	if (find_quote(str))
		join_quote(&str);
	if ((*exec)->out != STDOUT_FILENO)
		close_fd(&((*exec)->out));
	(*exec)->out = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((*exec)->out == -1)
	{
		perror(str);
		return (1);
	}
	return (0);
}

int	handle_redirout_append(char *str, t_exec **exec)
{
	if (find_quote(str))
		join_quote(&str);
	if ((*exec)->out != STDOUT_FILENO)
		close_fd(&((*exec)->out));
	(*exec)->out = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if ((*exec)->out == -1)
	{
		perror(str);
		return (1);
	}
	return (0);
}
