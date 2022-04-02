/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/03 14:42:23 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/02 19:57:21 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>//gettimeofday
#include <stdio.h>//printf
#include <unistd.h>//sleep
#include <stdlib.h>
#include <pthread.h>

#include "header.h"

static t_thread	*init_fork_values(t_forks *forks, t_args *args, int *start)
{
	int	i;
	t_thread	*th;

	i = 0;
	th = calloc(args->number_of_philosophers, sizeof(t_thread));
	if (!th)
		return (0);
	while (i < args->number_of_philosophers)
	{
		th[i].id = i + 1;
		th[i].forks = forks;
		th[i].values = args;
		th[i].start = start;
		pthread_mutex_init(&forks->mutex, 0);
		forks = forks->right;
		i++;
	}
	th[0].forks->left = fork_last(th[0].forks);
	return (th);
}

int main(int argc, char **argv)
{
	int	*start;
	t_args	*args;
	t_forks	*forks;
	t_thread	*th;
	pthread_t	*pthread_id;

	if (argc < 4)
		return (ft_write_error("Usage ./philo [number_of_philosophers] \
[time_to_die] [time_to_eat] [time_to_sleep]\n", 1));
	start = calloc(1, sizeof(int));
	if (!start)
		return (ft_write_error("Error, malloc failed!\n", 1));
	args = read_and_lexer(0, argv);
	if (!args)
		return (1);
	forks = init_forks(0, args, 0);
	if (!forks)
		return (ft_write_error("Error, creating forks failed!\n", 1));
	th = init_fork_values(forks, args, start);
	if (!th)
	{
		free(start);
		ft_free_forks(forks, args);
	}
	pthread_id = malloc(sizeof(pthread_t) * (args->number_of_philosophers + 1)); //+1 voor monitor thread
	if (!pthread_id)
	{
		free(start);
		ft_free_forks(forks, args);
		free(th);
	}
	if (create_threads(pthread_id, th, args))
	{
		ft_free_all(th, pthread_id);
		return (1);
	}
	if (join_threads(pthread_id, args))
	{
		ft_free_all(th, pthread_id);
		return (1);
	}
	printf("All threads closed expect for main thread!\n");
	ft_free_all(th, pthread_id);
	return 0;
}
