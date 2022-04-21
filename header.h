/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/08 16:35:10 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/21 18:26:05 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include "functions/functions.h"
# include "philos/philo.h"

typedef struct s_rules
{
	int			number_of_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			amount_of_times_to_eat;
}				t_rules;

typedef struct s_list
{
	t_rules			*rules;
	pthread_mutex_t	*forks_val;
	int				*in_use;
	struct s_philo	*ph;
}				t_list;

int		lexer(int argc, char **argv);
int		parse(t_list *v, char **argv);

int		init_forks(t_list *v);

int		create_and_start_threads(t_list *v);

void	*monitoring_thread(void *arg);

#endif