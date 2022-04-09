/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forks.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/08 17:10:14 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/09 13:53:42 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORKS_H
# define FORKS_H

#include <stdlib.h>

#include "../header.h"
#include <pthread.h>

typedef struct s_forks
{
	int		id;
	int		in_use;
	int		last;
	
	struct s_forks	*next;
	pthread_mutex_t fork;
	pthread_mutex_t value;
}				t_forks;

t_forks		*fork_create(void);
int			fork_add_back(t_forks *fork, int last);
t_forks		*fork_last(t_forks *fork);
void		freeforks(t_forks *forks);

#endif