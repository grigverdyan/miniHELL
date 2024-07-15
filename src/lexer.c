#include "minishell.h"

int	add_bool_operator(t_token_stream *t_stream, char *input, int i)
{
	if (input[i] == '&')
	{
		if (input[i + 1] == '&')
		{
			add_token(t_stream, TOKEN_AND, "&&");
			i += 1;
		}
		else
			clear_token_stream(t_stream, 
				"Minishell: syntax error near unexpected token `&'\n");
	}
	else if (input[i] == '|')
	{
		if (input[i + 1] == '|')
		{
			add_token(t_stream, TOKEN_OR, "||");
			++i;
		}
		else
			add_token(t_stream, TOKEN_PIPE, "|");
	}
	return i;
}

int	add_quote(t_token_stream *t_stream, char *input, int i)
{
	int start;

	start = ++i;
	if (input[i - 1] == '\'')
	{
		add_token(t_stream, TOKEN_QUOTE_SINGLE, "\'");
		while (input[i] && input[i] != '\'')
			i += 1;
		add_token(t_stream, TOKEN_WORD, ft_substr(input, start, i - start));
		if (input[i] != '\'')
			clear_token_stream(t_stream, "Single quote error!\n");
		add_token(t_stream, TOKEN_QUOTE_SINGLE, "\'");
	}
	else if (input[i - 1] == '\"')
	{
		add_token(t_stream, TOKEN_QUOTE_DOUBLE, "\"");
		while (input[i] && input[i] != '\"')
			i += 1;
		add_token(t_stream, TOKEN_WORD, ft_substr(input, start, i - start));
		if (input[i] != '\"')
			clear_token_stream(t_stream, "Double quote error!\n");
		add_token(t_stream, TOKEN_QUOTE_DOUBLE, "\"");
	}
	return i;
}

int	add_redirect(t_token_stream *t_stream, char *input, int i)
{
	if (input[i] == '<')
	{
		if (input[i + 1] == '<')
		{
			add_token(t_stream, TOKEN_HEREDOC, "<<");
			i += 1;
		}
		else
			add_token(t_stream, TOKEN_REDIRECT_IN, "<");
	}
	else
	{
		if (input[i + 1] == '>')
		{
			add_token(t_stream, TOKEN_APPEND, ">>");
			i += 1;
		}
		else
			add_token(t_stream, TOKEN_REDIRECT_OUT, ">");
	}
	return i;
}

int	add_env_var(t_token_stream *t_stream, char *input, int i)
{
	int start;

	start = i++;
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
		++i;
	add_token(t_stream, TOKEN_ENV_VAR, ft_substr(input, start, i - start));
	return i;
}

void    lexer(char *input, t_engine *e)
{
    int	start;
	int	i;

	i = -1;
    while (input[++i])
    {
        if (ft_isspace(input[i]))
            continue;
		if (input[i] == '&' || input[i] == '|')
			i = add_bool_operator(&e->t_stream, input, i);
        else if (input[i] == '<' || input[i] == '>')
			i = add_redirect(&e->t_stream, input, i);
        else if (input[i] == '\'' || input[i] == '\"')
			i = add_quote(&e->t_stream, input, i);
        else if (input[i] == '$')
			i = add_env_var(&e->t_stream, input, i);
        else if (input[i] == '*')
			add_token(&e->t_stream, TOKEN_WILDCARD, "*");
		else // TOKEN_WORD
        {
            start = i;
            while (input[i] && !ft_isspace(input[i]) && !is_token_type(input[i]))
            	++i;
            add_token(&e->t_stream, TOKEN_WORD, ft_substr(input, start, i - start));
			--i;
		}
    }
}
