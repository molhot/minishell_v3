/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_metacharacter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 22:04:25 by user              #+#    #+#             */
/*   Updated: 2023/03/02 11:34:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//|&;()<>\t\n

bool	is_metacharactert(char c)
{
	return (c && ft_strchr("|<>\n", c));
}