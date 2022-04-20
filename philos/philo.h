/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/08 18:55:01 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/20 15:48:09 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../header.h"
# include <pthread.h>
# include <unistd.h>

# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"
typedef struct s_time
{
	long			first_timestamp;
	long			timestamp_since_eaten;
	pthread_mutex_t	mutex;
}				t_time;

typedef struct	s_philo
{
	int				id;
	int				start;
	struct s_rules	*rules;
	struct s_forks	*forks;
	t_time			time;
	int				eat_count;
	pthread_mutex_t	eat_count_m;
	int				stop;
	pthread_mutex_t	stop_m;
}				t_philo;

typedef struct s_list t_list;

void	*philo(void *);
int		setup_philos(t_list *v);

int		ft_stop(t_philo *v);
int		ft_eaten_enough(t_philo *v);

void	ft_take_forks(t_philo *v);
void	ft_eat(t_philo *v);
void	ft_sleep(t_philo *v);
void	ft_think(t_philo *v);

#endif