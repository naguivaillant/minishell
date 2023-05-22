/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:32:12 by mrabourd          #+#    #+#             */
/*   Updated: 2023/05/22 17:26:35 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_cmd(t_data *data)
{
	int		i;
	char	**str;
	int		pos;

	pos = 0;
	i = 0;
	str = NULL;
	split_in_list(data, data->input);
	assign_type(data);
	print_all(data);
}