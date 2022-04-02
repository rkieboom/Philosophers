/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/06 13:39:47 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/02 19:38:19 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "forks/forks.h"
# include <stdlib.h>

typedef struct s_args
{
	int			number_of_philosophers;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			number_of_times_each_philosopher_must_eat;
}				t_args;
typedef struct s_thread
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

void		*philosophers(void *args);
void		*monitoring_thread(void *args);
long		get_time(void);

int		create_threads(pthread_t *pthread_id, t_thread *th, t_args *args);
int		join_threads(pthread_t *pthread_id, t_args *args);
int		ft_free_all(t_thread *th, pthread_t *pthread_id);

t_args		*read_and_lexer(t_args *args, char **argv);
t_forks		*init_forks(t_forks *forks, t_args *args, int i);
void		ft_free_forks(t_forks *forks, t_args *args);

size_t		ft_strlen(const char *str);
int			ft_atoi(const char *str);
long long	ft_atoi_l(const char *str);
int			ft_isdigit(int c);
int			ft_write_error(char *msg, int ret);

#endif