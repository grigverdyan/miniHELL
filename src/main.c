#include "minishell.h"
#include "debug.h"

void	error_message(char *text, int mode)
{
	if (mode == 0)
		perror(text);
	else if (text)
		ft_putstr_fd(text, 2);
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv, char **envp)
{
    t_engine	engine;
    char		*input;
    (void)argv;
    (void)envp;

    if (argc != 1)
		error_message("Minishell takes no argument! \n", 1);

    while (true)
    {
		if (isatty(STDIN_FILENO))
		{
			input = readline("Minishell$ ");
			if (!input)
				error_message("Input error!\n", 1);
			tokenizer(input, &engine);
		}
		else
			error_message("Minishell is not run in interactive mode!\n", 1);

		debug_print_tokens(&engine.lexer);
    }
    return (0);
}