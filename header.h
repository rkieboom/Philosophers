/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/06 13:39:47 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/02 14:36:16 by rkieboom      ########   odam.nl         */
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
	int				id;
	t_args			*values;
	t_forks			*forks;
	long			first_timestamp;
	long			timestamp_since_eaten;
	int				hungry;
	int				ready;
	int				*start;
}				t_thread;

void	*philosophers(void *args);
void	*monitoring_thread(void *args);
long	get_time(void);

#endif