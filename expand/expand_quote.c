/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_simplecommand.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 22:31:02 by marvin            #+#    #+#             */
/*   Updated: 2023/02/21 22:31:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	switch_quote_doller(char **args, char **newword)
{
	char	*tmp;

	tmp = *args;
	if (*tmp == '$' && (*(tmp + 1) == '\0' || \
	*(tmp + 1) == '\'' || *(tmp + 1) == '\"'))
	{
		append_char(&(*newword), *tmp);
		(*args)++;
	}
	else if (*tmp == '$' && *(tmp + 1) == '?')
		expand_dolleeques(&(*newword), &(*args), tmp);
	else if (*tmp == '$')
		expand_doller(&(*newword), &(*args), tmp);
}

static char	*expand_args_quote(char *args, char *args_free)
{
	char	*new_word;

	new_word = NULL;
	while (*args != '\0')
	{
		if (*args == '\\')
			b_slush_append(&args, &new_word);
		else if ((*args == '\'' || *args == '\"') && *(args + 1) != '\0')
			quote_append(&args, &new_word);
		else if (*args == '$')
			switch_quote_doller(&args, &new_word);
		else
			append_char(&new_word, *args++);
	}
	free(args_free);
	return (new_word);
}

void	expand_quote(t_token *token)
{
	while (token != NULL)
	{
		if (token->word != NULL)
			token->word = expand_args_quote(token->word, token->word);
		token = token->next;
	}
}
