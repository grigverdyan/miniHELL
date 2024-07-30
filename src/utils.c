#include "minishell.h"

void	error_message(char *text, bool is_errno)
{
	if (is_errno)
		perror(text);
	else if (text)
		ft_putstr_fd(text, 2);
	exit(EXIT_FAILURE);
}

void	init_engine(t_engine *engine, char **envp)
{
	engine->envp = envp;
	engine->stream.head = NULL;
	engine->stream.tail = NULL;
}
