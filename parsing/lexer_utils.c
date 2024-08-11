/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:04:20 by elchakir          #+#    #+#             */
/*   Updated: 2024/08/11 05:26:21 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_v2(const char **p, char *special, TokenType *type)
{
	if (**p == '>')
	{
		if (*(*p + 1) == '>')
		{
			special[0] = '>';
			special[1] = '>';
			special[2] = '\0';
			*type = TOKEN_APPEND_OUT;
			(*p)++;
		}
		else if (**p == '>' && *(*p + 1) != '>')
			*type = TOKEN_REDIRECT_OUT;
	}
}

void	handle_special_characters(const char **p, Token *tokens,
		int *num_tokens)
{
	TokenType	type;
	char		special[4];

	type = TOKEN_WORD;
	if (**p == '|' || **p == '<' || **p == '>' || **p == '&' || **p == '#')
	{
		special[0] = **p;
		special[1] = '\0';
		type = TOKEN_WORD;
		if (**p == '|' && *(*p + 1) != '|')
			type = TOKEN_PIPE;
		else if (**p == '|' && *(*p + 1) == '|')
			type = TOKEN_OR;
		else if (**p == '>')
			handle_v2(p, special, &type);
		else
			handel_else(p, special, &type);
		add_token(tokens, num_tokens, type, special);
		(*p)++;
		return ;
	}
	else
		handel_q(p, type, tokens, num_tokens);
}

int check_here_doc(Token *tokens, int *num_tokens)
{
    if (*num_tokens > 0 && 
        (tokens[*num_tokens - 1].type == TOKEN_HERE_DOC ||
         tokens[*num_tokens - 1].type == TOKEN_HERE_DOC_NO))
    {
        return 1;
    }
    return 0;
}
