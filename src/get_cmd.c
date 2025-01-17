/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 21:32:51 by nsalhi            #+#    #+#             */
/*   Updated: 2023/10/12 07:30:44 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_cmd_norm(char *cmd, DIR **dir, int *count)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
	{
		if (ft_strlen(cmd) == 1 && cmd[0] == '.')
		{
			closedir(*dir);
			ft_fprintf(2, "filename argument required\n");
			return (2);
		}
		if (cmd[i] == '.')
			(*count)++;
		(i)++;
	}
	return (EXIT_SUCCESS);
}

char	*get_cmd_normbis(char **cmd_path, DIR *dir, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*cmd_path && cmd_path != NULL)
	{
		tmp = ft_strjoin(*cmd_path, "/");
		command = ft_strjoin(tmp, cmd);
		dir = opendir(command);
		if (dir)
		{
			closedir(dir);
			ft_fprintf(2, "%s: Is a directory\n", cmd);
			return (free(tmp), free(command), "126");
		}
		if (dir)
			closedir(dir);
		if (command != NULL && access(command, X_OK) == 0 && verif_cmd(command))
			return (free(tmp), command);
		free(tmp);
		free(command);
		cmd_path++;
	}
	return (NULL);
}

char	*return_isdir(DIR *dir, char *cmd)
{
	closedir(dir);
	ft_fprintf(2, "%s: Is a directory\n", cmd);
	return ("126");
}

char	*is_dir_norm(DIR *dir, char *cmd)
{
	if (dir)
		closedir(dir);
	return (command_not_found(cmd));
}

char	*get_cmd(char **cmd_path, char *cmd)
{
	DIR		*dir;
	int		count;
	char	*result_cmd;

	count = 0;
	dir = opendir(cmd);
	if (get_cmd_norm(cmd, &dir, &count) == 2)
		return ("2");
	if (ft_strlen(cmd) == 0 || count == (int)ft_strlen(cmd))
		return (is_dir_norm(dir, cmd));
	if (dir || (ft_strlen(cmd) == 1 && cmd[0] == '~'))
		return (return_isdir(dir, cmd));
	if (dir)
		closedir(dir);
	if (cmd != NULL && ft_strchr(cmd, '/') && access(cmd, X_OK) == 0)
		return (ft_strjoin("", cmd));
	if (cmd_path != NULL && cmd_path[0] != NULL)
	{
		result_cmd = get_cmd_normbis(cmd_path, dir, cmd);
		if (result_cmd != NULL)
			return (result_cmd);
	}
	return (command_not_found(cmd));
}
