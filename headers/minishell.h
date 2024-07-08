#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

# include "libft.h"

typedef enum e_token_type
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
	TOKEN_QUESTION_MARK,
	TOKEN_WILDCARD
} t_token_type;

typedef struct s_token
{
    t_token_type	type;
    char			*value;
    struct s_token	*next;
} t_token;

typedef struct s_lexer
{
	size_t	count;
    t_token	*head;
	t_token	*tail;
} t_lexer;

typedef struct s_engine
{
	char**	envp;
	t_lexer lexer;
} t_engine;

void	parse_redirect(t_lexer *lexer, char *input, int *i);
void	parse_quote(t_lexer *lexer, char *input, int *i);
void	add_token(t_lexer *lexer, t_token_type type, char *value);
void    tokenizer(char *input, t_engine *e);

#endif  /* MINISHELL_H */