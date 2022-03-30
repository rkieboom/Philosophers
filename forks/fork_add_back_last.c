/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_add_back_last.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/06 15:22:51 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/03/06 16:31:58 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "forks.h"

void	fork_add_back_last(t_forks **alst, t_forks *new)
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
		new->right = *alst;
		new->last = 1;
	}
	else
		fork_add_front(alst, new);
}