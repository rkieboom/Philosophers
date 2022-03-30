/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_fork.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/06 13:38:38 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/03/06 16:22:34 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "forks.h"

t_forks	*fork_create(void)
{
	t_forks *lst;

	lst = ft_calloc(1, sizeof(t_forks));
	if (lst == NULL)
		return (NULL);
	return (lst);
}