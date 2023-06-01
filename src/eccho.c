#include "../include/minishell.h"

void	print_lines(int i, char **str, int fd)
{
	while (str[i])
	{
		ft_putstr_fd(str[i++], fd);
		if (str[i])
			ft_putchar_fd(' ', fd);
	}
}

int	mini_echo(t_data *data)
{
	int		i;
	int		j;
	int		status;

	i = 1;
	status = 0;
	while (data->cmd[i] && data->cmd[i][0] == '-'
		&& data->cmd[i][1] == 'n')
	{
		j = 1;
		while (data->cmd[i][j] == 'n')
			j++;
		if (data->cmd[i][j] == '\0')
			status = 1;
		else
			break ;
		i++;
	}
	if (status == 1)
		print_lines(i, data->cmd, STDOUT_FILENO);
	if (status == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
