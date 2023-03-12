/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ready.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:39:39 by user              #+#    #+#             */
/*   Updated: 2023/03/02 12:37:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name(char *name_and_value)
{
	size_t	len;
	size_t	j;
	char	*name;

	len = 0;
	while (name_and_value[len] != '\0')
	{
		if (name_and_value[len] == '=')
			break ;
		len++;
	}
	name = malloc(sizeof(char) * (len + 1));
	if (!name)
		fatal_error("malloc");
	j = 0;
	while (len)
	{
		name[j] = name_and_value[j];
		j++;
		len--;
	}
	name[j] = '\0';
	return (name);
}

void	env_init(t_map **env)
{
	size_t			i;
	char			*name;
	char			*value;
	char			cwd[256];
	extern char		**environ;

	i = 0;
	*env = malloc(sizeof(t_map));
	(*env)->err_status = 0;
	(*env)->item_head = NULL;
	while (environ[i] != NULL)
	{
		name = get_name(environ[i]);
		value = getenv(name);
		map_set(env, name, value);
		free(name);
		i++;
	}
	getcwd(cwd, sizeof(cwd));
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		fatal_error("getcwd");
	map_set(env, "PWD", cwd);
}
