/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/08 18:55:01 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/09 14:08:59 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../header.h"

typedef struct s_time
{
	long			first_timestamp;
	long			timestamp_since_eaten;
}				t_time;

typedef struct	s_philo
{
	int				id;
	struct s_rules	*rules;
	struct s_forks	*forks;
	struct s_time	time;
	int				eat_count;
}				t_philo;

typedef struct s_list t_list;

void	*philo(void *);
int		setup_philos(t_list *v);

#endif