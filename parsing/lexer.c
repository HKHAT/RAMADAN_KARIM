/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:20:21 by elchakir          #+#    #+#             */
/*   Updated: 2024/08/10 23:44:43 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_quotes_and_wordsv2(const char **p, QuoteWordParserState **state)
{
	if ((*state)->in_quotes)
	{
		if (**p == (*state)->quote_char)
		{
			(*state)->in_quotes = 0;
			(*state)->quote_char = '\0';
		}
	}
	else
	{
		(*state)->in_quotes = 1;
		(*state)->quote_char = **p;
	}
}

char	*expand_variable(const char *start, int length, t_env_node *env)
{
	char	*varname;
	char	*value;
	char *s;
	varname = ft_malloc(length + 1);
	ft_strncpy(varname, start, length);
	varname[length] = '\0';
	value = ft_getenv(env, varname);
	if (value)
	{
		s = ft_malloc(ft_strlen(value) + 1);
		ft_strncpy(s,value,ft_strlen(value));
		return (s);
	}
	else
	{
		s = ft_malloc(1);
		s[0] = '\0';
		return (s);
	}
}

int	is_ambiguous(const char *expanded_value)
{
	return (ft_strrch_finder((char *)expanded_value, ' ') != NULL
		|| expanded_value[0] == '\0' || !expanded_value);
}

char	*alloc_token(const char *s, int *r, int i)
{
	char	*buf;
	int		size;
	int		j;
	int		rem;

	j = 0;
	size = 0;
	rem = i;
	while (s[i] && s[i] != 32 && !(s[i] >= 9 && s[i] <= 13))
	{
		size++;
		i++;
	}
	buf = ft_malloc(size + 1);
	if (!buf)
		return (NULL);
	while (j < size)
	{
		buf[j] = s[rem];
		j++;
		rem++;
	}
	buf[j] = '\0';
	*r = rem;
	return (buf);
}

int	lex(const char *input, Token *tokens, int *num_tokens, t_env_node *env)
{
	const char				*p;
	QuoteWordParserState	state;

	p = input;
	state = init_lexer(env);
	while (*p)
	{
		skip_whitespace(&p);
		handle_special_characters(&p, tokens, num_tokens);
		handle_quotes_and_words(&p, tokens, num_tokens, &state);
	}
	if (state.in_quotes)
	{
		printf("Syntax error: unclosed quote '%c'\n", state.quote_char);
		return (state.in_quotes);
	}
	add_token(tokens, num_tokens, TOKEN_END, "");
	return (0);
}
