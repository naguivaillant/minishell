#include "minishell.h"

void	print_lines(int i, char **str, int fd)
{
	while (str[i])
	{
		ft_putstr_fd(str[i++], fd);
		if (str[i])
			ft_putchar_fd(' ', fd);
	}
}

int	mini_echo(t_data *cmd)
{
	int		i;
	int		j;
	int		status;

	i = 1;
	status = 0;
	while (cmd->str[i] && cmd->str[i][0] == '-'
		&& cmd->str[i][1] == 'n')
	{
		j = 1;
		while (cmd->str[i][j] == 'n')
			j++;
		if (cmd->str[i][j] == '\0')
			status = 1;
		else
			break ;
		i++;
	}
	if (satuts == 1)
		print_lines(i, cmd->str, STDOUT_FILENO);
	if (status == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
