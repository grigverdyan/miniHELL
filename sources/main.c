#include "libft.h"
#include "minishell.h"
#include "tokenizer.h"

#include <stdio.h>

int main(int argc, char **argv, char ***envp)
{
    t_token *tokens;
    char *input;

    if (argc != 1)
    {
        printf("Minishell takes no argument\n", 2);
        exit(EXIT_FAILURE);
    }    
    while (1)
    {
        input = readline("minishell: ");
        if (!line)
        {
            //
        }
        tokenize(input, &tokens);
    }
    e
}