#include "minishell.h"

int	heredoc_count(char **tab)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (tab[++i])
	{
		if (tab[i][0] == '<' && tab[i][1] == '<')
			count++;
	}
	return (count);
}

void	dup_n_close(int oldfd, int newfd)
{
	safe_dup(oldfd, newfd); //a faire
	safe_close(oldfd); // a faire
}
