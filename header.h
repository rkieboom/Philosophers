/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/06 13:39:47 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/03/31 16:16:57 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "forks/forks.h"

typedef struct	s_args {
	int			number_of_philosophers;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			number_of_times_each_philosopher_must_eat;
}				t_args;

typedef struct	s_thread
{
	pthread_t		*pthread_id;
	int				id;
	t_args			*values;
	t_forks			*forks;
	long			first_timestamp;
	long			timestamp_since_eaten;
	int				hungry;
	int				stop;
}				t_thread;

void	*philosophers(void *args);

#endif