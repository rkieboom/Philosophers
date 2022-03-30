/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_add_front.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/06 15:13:39 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/03/06 15:16:48 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "forks.h"

void	fork_add_front(t_forks **alst, t_forks *new)
{
	new->right = *alst;
	*alst = new;
}