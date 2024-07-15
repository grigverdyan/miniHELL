#include "minishell.h"
#include "debug.h"

void	error_message(char *text, bool is_errno)
{
	if (is_errno)
		perror(text);
	else if (text)
		ft_putstr_fd(text, 2);
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv, char **envp)
{
    (void)argv;
    (void)envp;

    t_engine	engine;
    char		*input;

    if (argc != 1)
		error_message("Minishell takes no argument! \n", false);

	engine.t_stream.head = NULL;
	engine.t_stream.tail = NULL;
    while (true)
    {
		if (isatty(STDIN_FILENO))
		{
			input = readline("Minishell$ ");
			if (!input)
				error_message("Input error!\n", false);
			lexer(input, &engine);
		}
		else
			error_message("Minishell isn't run in interactive mode!\n", false);

		debug_print_tokens(&engine.t_stream);
    }
    return (0);
}