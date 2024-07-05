#include "libft.h"
#include "tokenizer.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

t_token *create_token(e_token_type type, char *value)
{
    t_token *token;

    token = (t_token *)malloc(sizeof(t_token));
    if (!token)
    {
        perror("Failed to allocate memory for token");
        exit(EXIT_FAILURE);
    }
    token->type = type;
    // if (!value)
    //     return (NULL);
    token->value = ft_strdup(value);
    if (!token->value)
    {
        free(token);
        perror("Failed to duplicate token value");
        exit(EXIT_FAILURE);
    }
    token->next = NULL;
    return (token);

}

void add_token(t_token *head, e_token_type type, char *value)
{
    t_token *token;
    t_token *temp_token;

    token = create_token(type, value);
    if (head == NULL)
    {
        head = token;
    }
    else
    {
        temp_token = head;
        while (temp_token->next != NULL)
        {
            temp_token = temp_token->next;
        	//head = head->next;
		}
        temp_token->next = token;
    	//head->next = token;
	}
}


void    tokenize(char *input, t_token *tokens)
{
    char    *start;

    while (*input)
    {
        if (ft_isspace(*input))
        {
            input++;
            continue;
        }
        if (*input == '|')
        {
            add_token(tokens, TOKEN_PIPE, "|");
            input++;
        }
        else if (*input == '<')
        {
            if (*(input + 1) == '<')
            {
                add_token(tokens, TOKEN_HEREDOC, "<<");
                input += 2;
            }
            else
            {
                add_token(tokens, TOKEN_REDIRECT_IN, "<");
                input++;
            }
        }
        else if (*input == '>')
        {
            if (*(input + 1) == '>')
            {
                add_token(tokens, TOKEN_APPEND, ">>");
                input += 2;
            }
            else
            {
                add_token(tokens, TOKEN_REDIRECT_OUT, ">");
                input++;
            }
        }
        else if (*input == '\'')
        {
            input++;
            start = input;
            while (*input != '\'' && *input != '\0')
                input++;
            add_token(tokens, TOKEN_QUOTE_SINGLE, ft_strndup(start, input - start));
            input++;
        }
        else if (*input == '\"')
        {
            input++;
            start = input;
            while (*input != '\"' && *input != '\0')
                input++;
            add_token(tokens, TOKEN_QUOTE_DOUBLE, ft_strndup(start, input - start));
            input++;
        }
        else if (*input == '$')
        {
            input++;
            start = input;
            while (isalnum(*input) || *input == '_')
                input++;
            add_token(tokens, TOKEN_ENV_VAR, ft_strndup(start, input - start));
        }
        else if (*input == '&' && *(input + 1) == '&')
        {
            add_token(tokens, TOKEN_AND, "&&");
            input += 2;
        }
        else if (*input == '|' && *(input + 1) == '|')
        {
            add_token(tokens, TOKEN_OR, "||");
            input += 2;
        }
        else
        {
            start = input;
            while (!ft_isspace(*input) && *input != '|' && *input != '<' && *input != '>' && *input != '\0')
                input++;
            add_token(tokens, TOKEN_WORD, ft_strndup(start, input - start));
        }
    }
    add_token(tokens, TOKEN_EOF, NULL);
}
