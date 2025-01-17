/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_synthax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:50:37 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/11 19:52:07 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exit_syntax_error(char *rline)
{
	write(2, "minishell: Invalid Syntax at token\n", 36);
	free(rline);
	return (2);
}

int	exit_syntax_error_nl(char *rline)
{
	write(2, "minishell: Syntax error near unexpected token 'newline'\n", 56);
	free(rline);
	return (2);
}

int	exit_syntax_error_near(char *rline)
{
	write(2, "syntax error near unexpected token\n", 35);
	free(rline);
	return (2);
}
