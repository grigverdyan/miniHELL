#include "libft.h"
#include "minishell.h"
#include "tokenizer.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char **argv, char **envp)
{
    t_token *tokens;
    char *input;
    (void)argv;
    (void)envp;

    if (argc != 1)
    {
        printf("Minishell takes no argument\n");
        exit(EXIT_FAILURE);
    }
    tokens = (t_token *)malloc(sizeof(t_token)); 
    while (1)
    {
        input = readline("Minishell$");
        if (!input)
        {
            //
        }
        tokenize(input, tokens);
    }
    return (0);
}