#include "minishell.h"

bool	is_token_type(char c)
{
	return (c == '&' || c == '|' || c == '<' || c == '>' ||
		c == '\'' || c == '\"' || c == '$' || c == '*');
}

void	add_token(t_token_stream *t_stream, t_token_type type, char *value)
{
    t_token *token;

	token = (t_token *)malloc(sizeof(t_token));
    if (!token)
		clear_token_stream(t_stream, "Failed to allocate memory for token!\n");
    token->type = type;
    token->next = NULL;
	if (type != TOKEN_WORD)
    	token->value = ft_strdup(value);
	else
		token->value = value;
    if (!token->value)
    {
        free(token);
		clear_token_stream(t_stream, "Failed to set token value!\n");
    }
    if (!t_stream->tail)
        t_stream->head = token;
	else
		t_stream->tail->next = token;
	t_stream->tail = token;
}

void    clear_token_stream(t_token_stream *t_stream, char *text)
{
    t_token *head;
    t_token *tmp;

    if (!t_stream)
        return;

    head = t_stream->head;
    while (head)
    {
        tmp = head->next;
        free(head->value);
        free(head);
        head = tmp;
    }
    t_stream->head = NULL;
    t_stream->tail = NULL;
    if (text)
        error_message(text, false);
}