#include "libft.h"
#include "tokenizer.h"
#include <stdlib.h>

int is_space(char c)
{
    if (c == ' ' || c == '\t' || c == '\n'
        || c == '\v' || c == '\f' || c == '\r')
        return (1);
    return (0);
}

t_token *create_token(e_token_type type, char *value)
{
    t_toekn *token;

    token = (t_token *)malloc(sizeof(t_token));
    if (!token)
    {
        // exit functions
    }
    token->type = type;
    token->value = ft_strdup(value);
    token->next = NULL;
    return (token);

}

void    add_token(t_toekn **head, e_token_type type, char *value)
{
    t_token *token;
    t_token *temp_token;

    token = create_token(type, value);
    if (*head == NULL)
    {
        *head = token;
    }
    else
    {
        *temp_token = *head;
        while (temp_token->next != NULL)
        {
            temp_token = temp_token->next;
        }
        temp_token->next = token;
    }
}

t_token *tokenize(char *input, t_token **tokens)
{
    while (*input)
    {
        if (is_space(*input))
        {
            input++;
            continue;
        }
        
    }
}