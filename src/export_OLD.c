#include "../include/minishell.h"

	/* --- Mark each name to be passed to child processes in the environment. The names
refer to shell variables*/
	/*If no names are supplied, a list of names of all exported variables is displayed.*/
	/*If a variable name is followed by =value, the value of the variable is set to value.*/
	/*The return status is zero unless 
one of the names is not a valid shell variable name. --- */

/* PAS BESOIN DE FAIRE CA-----------------
void	ft_sort(t_list *tmp, t_list *print)
{
	while (print->next && print->printed == 1)
		print = print->next;
	while (tmp && tmp->next != NULL)
	{
		if (ft_strncmp(print->content, tmp->content, ft_strlen(tmp->content)) < 0)
			tmp = tmp->next;
		if (ft_strncmp(print->content, tmp->content, ft_strlen(tmp->content)) >= 0)
		{
			if (tmp->printed == 0)
				print = tmp;
			tmp = tmp->next;
		}
	}
	print->printed = 1;
	printf("declare -x %s\n", (char *)print->content);
}

void	back_to_zero(t_data *data)
{
	t_list	*tmp;

	tmp = data->env;
	while (tmp != NULL)
	{
		// tmp->full = 0;
		tmp->printed = 0;
		tmp = tmp->next;
	}
}


SERT A RIEN FINALEMENT-----

char	*extract_value(t_data *data, t_list *pos)
{
	char	*value;
	int		i;
	int		y;

	y = 0;
	i = 0;
	value = NULL;
	while (pos->content[i] != '=')
		i++;
	while (pos->content[i] != '\0')
	{
		i++;
		y++;
	}
	value = malloc(sizeof(char) * y);
	if (value == NULL)
		exit_all(data, 1, "Problem of malloc when extract value(export)");
	value = ft_strchr(pos->content, '=');
	return (value);
}

*/


/* CMD IN TAB OLD*/
// void	put_cmd_in_tab(t_data *data, int nb)
// {
// 	t_list	*tmp;
// 	int		i;
// 	int		tab;

// 	i = 0;
// 	tmp = data->token_list;
// 	tab = count_cmd(data);
// 	if (tab < 1)
// 		exit_all(data, 1, "There is no command");
// 	data->exec[nb].cmd = malloc(sizeof(char *) * (tab + 1));
// 	if (data->exec[nb].cmd == NULL || !data->exec[nb].cmd)
// 		exit_all(data, 1, "probleme de malloc sur la tab de cmd");
// 	while (tmp != NULL)
// 	{
// 		if (tmp->type != INFILE && tmp->type != OUTFILE
// 			&& tmp->type != REDIRECT_INPUT && tmp->type != REDIRECT_OUTPUT
// 			&& tmp->type != OUTFILE && tmp->type != HEREDOC
// 			&& tmp->type != ENDOFFILE && i <= tab)
// 		{
// 			data->exec[nb].cmd[i] = ft_strdup(tmp->content);
// 			i++;
// 		}
//		tmp = tmp->next;
// 	}
// 	data->exec[nb].cmd[i] = NULL;
// }
