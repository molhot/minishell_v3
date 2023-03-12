/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:20:06 by user              #+#    #+#             */
/*   Updated: 2023/03/12 20:30:03 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*value_ready(char *value)
{
	char	*new_value;

	new_value = NULL;
	while (*value != '\0')
	{
		if (*value == '\\')
			value++;
		append_char(&new_value, *value);
		value++;
	}
	return (new_value);
}

void	ms_env(void)
{
	t_item	*itr;
	char	*value_cpy;

	itr = g_env->item_head;
	while (itr != NULL)
	{
		value_cpy = value_ready(itr->value);
		printf("%s=%s\n", itr->name, value_cpy);
		itr = itr->next;
		free(value_cpy);
	}
}
