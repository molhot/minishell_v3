/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 23:22:25 by user              #+#    #+#             */
/*   Updated: 2023/03/10 14:33:59 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redirect	*tok_to_redirect_f(bool *flag, t_node *node, t_token **tok)
{
	parse_redirect(&(*node->command->redirect), &(*tok));
	(*node->command->redirect)->ambigous = false;
	*flag = false;
	(*node->command->redirect)->before = NULL;
	return (*node->command->redirect);
}

t_redirect	*tok_to_redirect(t_redirect *redirect, t_token **tok)
{
	parse_redirect(&(redirect->next), &(*tok));
	redirect->next->ambigous = false;
	redirect->next->before = redirect;
	return (redirect->next);
}

bool	parse_redirect(t_redirect **redirect, t_token **tok)
{
	*redirect = malloc(sizeof(t_redirect));
	if (ft_strcmp((*tok)->word, ">") == 0 && \
	ft_strcmp((*tok)->next->word, ">") == 0)
	{
		(*redirect)->type = APPEND;
		*tok = (*tok)->next;
	}
	else if (ft_strcmp((*tok)->word, "<") == 0 \
	&& ft_strcmp((*tok)->next->word, "<") == 0)
	{
		(*redirect)->type = HEREDOC;
		*tok = (*tok)->next;
	}
	else if (ft_strcmp((*tok)->word, "<") == 0)
		(*redirect)->type = IN;
	else
		(*redirect)->type = OUT;
	if ((*tok)->next->kind == TK_WORD)
		(*redirect)->file_path = ft_strdup((*tok)->next->word);
	return (true);
}

void	free_redirect(t_redirect *redirect)
{
	t_redirect	*next;

	if (redirect == NULL)
		return ;
	next = redirect->next;
	if (redirect->file_path != NULL)
		free(redirect->file_path);
	free(redirect);
	free_redirect(next);
}

void	ready_redirectinout(t_node *node, bool *flag, bool f_content)
{
	if (f_content == true)
		node->command->redirect = \
		(t_redirect **)malloc(sizeof(t_redirect *) * 1);
	node->command->in_fd[0] = STDIN_FILENO;
	node->command->in_fd[1] = -1;
	node->command->out_fd[0] = -1;
	node->command->out_fd[1] = STDOUT_FILENO;
	*flag = true;
}
