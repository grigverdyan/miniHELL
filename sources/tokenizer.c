#include "minishell.h"

void	parse_redirect(t_lexer *lexer, char *input, int *i)
{
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			add_token(lexer, TOKEN_HEREDOC, "<<");
			*i += 1;
		}
		else
			add_token(lexer, TOKEN_REDIRECT_IN, "<");
	}
	else
	{
		if (input[*i + 1] == '>')
		{
			add_token(lexer, TOKEN_APPEND, ">>");
			*i += 1;
		}
		else
			add_token(lexer, TOKEN_REDIRECT_OUT, ">");
	}
}

void	add_token(t_lexer *lexer, t_token_type type, char *value)
{
    t_token *token;

	token = (t_token *)malloc(sizeof(t_token));
    if (!token)
		;
		//destroy_tokens(lexer, "Failed to allocate memory for token: ", 0);
    token->type = type;
    token->next = NULL;
	if (type != TOKEN_WORD)
    	token->value = ft_strdup(value);
	else
		token->value = value;
    if (!token->value)
    {
        free(token);
		//destroy_tokens(lexer, "Failed to duplicate token value: ", 0);
    }
    if (!lexer->tail)
        lexer->head = token;
	else
		lexer->tail->next = token;
	lexer->tail = token;
}

void    tokenizer(char *input, t_engine *e)
{
    int	start;
	int	i;

	i = -1;
    while (input[++i])
    {
        if (ft_isspace(input[i]))
            continue;
		if (ft_isalnum(input[i]))
        {
            start = i;
            while (ft_isalnum(input[i]))
            	++i;
            add_token(&e->lexer, TOKEN_WORD, ft_substr(input, start, i - start));
		}
    	if (input[i] == '&' && input[i + 1] == '&')
        {
            add_token(&e->lexer, TOKEN_AND, "&&");
            ++i;
        }
        else if (input[i] == '|' && input[i + 1] == '|')
        {
            add_token(&e->lexer, TOKEN_OR, "||");
        	++i;
        }
        else if (input[i] == '|')
            add_token(&e->lexer, TOKEN_PIPE, "|");
        else if (input[i] == '<' || input[i] == '>')
			parse_redirect(&e->lexer, input, &i);
        else if (input[i] == '\'')
            add_token(&e->lexer, TOKEN_QUOTE_SINGLE, "\'");
        else if (input[i] == '\"')
            add_token(&e->lexer, TOKEN_QUOTE_DOUBLE, "\"");
		else if (input[i] == '?')
			add_token(&e->lexer, TOKEN_QUESTION_MARK, "?");
        else if (input[i] == '$')
			add_token(&e->lexer, TOKEN_ENV_VAR, "$");
        else if (input[i] == '*')
			add_token(&e->lexer, TOKEN_WILDCARD, "*");

    }
}
