#ifndef TOKENIZER_H
# define TOKENIZER_H

typedef enum
{
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT,
    TOKEN_APPEND,
    TOKEN_HEREDOC,
    TOKEN_ENV_VAR,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_QUOTE_SINGLE,
    TOKEN_QUOTE_DOUBLE,
    TOKEN_EOF
} e_token_type;

typedef struct s_token
{
    e_token_type type;
    char *value;
    struct t_token *next;
} t_token;

t_token *create_token(e_token_type type, char *value);
void    add_token(t_toekn **head, e_token_type type, char *value);

#endif /* TOKENIZER_H */