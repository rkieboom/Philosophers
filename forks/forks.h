/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forks.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/06 13:39:38 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/06 21:15:41 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORKS_H
# define FORKS_H

# include <unistd.h>
# include <pthread.h>

typedef struct s_forks
{
	struct s_forks	*left;
	struct s_forks	*right;
	int				in_use;
	int				last;
	pthread_mutex_t	fork;
	pthread_mutex_t	value;
}					t_forks;

t_forks		*fork_create(void);
void		fork_add_back(t_forks **alst, t_forks *new);
void		fork_add_front(t_forks **alst, t_forks *new);
void		fork_add_back_last(t_forks **alst, t_forks *new);
t_forks		*fork_last(t_forks *lst);

void		*ft_calloc(size_t count, size_t size);

#endif
