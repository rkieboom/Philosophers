/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_add_back.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/06 15:12:33 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/03/06 16:23:17 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "forks.h"

void	fork_add_back(t_forks **alst, t_forks *new)
{
	t_forks *nlist;

	if (!alst)
		return ;
	else if (*alst)
	{
		nlist = *alst;
		nlist = fork_last(*alst);
		nlist->right = new;
		new->left = nlist;
	}
	else
		fork_add_front(alst, new);
}