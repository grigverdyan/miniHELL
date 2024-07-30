#ifndef MINISHELL_H
#define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

#include "libft.h"

typedef enum e_token_type
{
    TOKEN_OR,
    TOKEN_AND,
    TOKEN_PIPE,
    TOKEN_WORD,
    TOKEN_APPEND,
    TOKEN_HEREDOC,
    TOKEN_ENV_VAR,
	TOKEN_WILDCARD,
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT,
    TOKEN_QUOTE_SINGLE,
    TOKEN_QUOTE_DOUBLE
}   t_token_type;

typedef struct s_token
{
    t_token_type	type;
    char			*value;
    struct s_token	*next;
}   t_token;

typedef struct s_stream
{
    t_token	*head;
	t_token	*tail;
}   t_stream;

typedef struct s_engine
{
	char**      envp;
	t_stream    stream;
}   t_engine;

typedef enum e_node_type
{
    OR,
    AND,
    PIPE,
    COMMAND
}   t_node_type;

typedef struct s_ast_node
{
    t_node_type type;
    char        *cmd;
    char        *arg;
    char        *redir_in;
    char        *redir_out;
}   t_ast_node;

// utils.c
void	error_message(char *text, bool is_errno);
void	init_engine(t_engine *engine, char **envp);

// lexer.c
int     add_bool_operator(t_stream *stream, char *input, int i);
int     add_quote(t_stream *stream, char *input, int i);
int     add_redirect(t_stream *stream, char *input, int i);
int     add_env_var(t_stream *stream, char *input, int i);
void    lexer(char *input, t_stream *stream);

// lexer_utils.c
bool	is_token_type(char c);
void    add_token(t_stream *stream, t_token_type type, char *value);
void    clear_token_stream(t_stream *stream, char *text);



#endif  /* MINISHELL_H */