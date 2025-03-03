/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:16:02 by ekeisler          #+#    #+#             */
/*   Updated: 2025/02/26 14:18:48 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int		is_space_or_operator(char c);
static void		add_t(char **tokens, int *i, const char *start,
					const char *end);
static int		count_tokens(const char *str);
static void		process_t(const char **str, const char **start,
					char **t, int *i);

/* @utils: pars our command (flags, input...) 	   */
/* @return: return our input parsed (char **)token */
char	**split_token(const char *str)
{
	int			token_count;
	char		**tokens;
	int			index;
	const char	*start;

	token_count = count_tokens(str);
	tokens = (char **)malloc(sizeof(char *) * (token_count + 1));
	if (!tokens)
		exit(1);
	index = 0;
	start = NULL;
	while (*str)
	{
		process_t(&str, &start, tokens, &index);
		str++;
	}
	if (start)
		add_t(tokens, &index, start, str);
	tokens[index] = NULL;
	return (tokens);
}

/* @utils: Count numbers of tokens necessary for the memorry allocation */
/* @return: count of tokens (int)                                       */
static int	count_tokens(const char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (!is_space_or_operator(*str))
		{
			count++;
			while (*str && !is_space_or_operator(*str))
				str++;
		}
		else
			str++;
	}
	return (count);
}

static int	is_space_or_operator(char c)
{
	if (c == ' ' || c == '|' || c == '<' || c == '>')
		return (1);
	if (c == '\\' || c == ';')
		return (2);
	return (0);
}

/* @utils:  decide if a token will be added or rejected */
/* @return: none                                        */
static void	process_t(const char **str, const char **start, char **t, int *i)
{
	char	quote_type;

	if (**str == '"' || **str == '\'')
	{
		quote_type = **str;
		if (!*start)
			*start = *str;
		(*str)++;
		while (**str && **str != quote_type)
			(*str)++;
	}
	else if (is_space_or_operator(**str) == 2)
	{
		(*str)++;
		if (!**str)
			return ;
	}
	else if (!is_space_or_operator(**str))
	{
		if (!*start)
			*start = *str;
	}
	else
	{
		if (*start)
		{
			add_t(t, i, *start, *str);
			*start = NULL;
		}
	}
}

/* @utils: alloc memmory for each token then copy it in our array */
/* @return: none                                                  */
static void	add_t(char **tokens, int *i, const char *start, const char *end)
{
	size_t	length;

	length = end - start;
	tokens[*i] = (char *)malloc(length + 1);
	if (!tokens[*i])
		exit(1);
	ft_strncpy(tokens[*i], start, length);
	tokens[*i][length] = '\0';
	(*i)++;
}
