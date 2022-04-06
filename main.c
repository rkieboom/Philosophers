/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/03 14:42:23 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/06 21:24:53 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

#include "header.h"

static t_thread	*init_fork_values(t_forks *forks, t_args *args, int *start)
{
	int			i;
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
		pthread_mutex_init(&th[i].mutex, 0);
		pthread_mutex_init(&forks->fork, 0);
		pthread_mutex_init(&forks->value, 0);
		forks = forks->right;
		i++;
	}
	if (args->number_of_philosophers != 1)
		th[0].forks->left = fork_last(th[0].forks);
	else
		th[0].forks->last = 1;
	return (th);
}

static int	run(pthread_t *pthread_id, t_thread *th, t_args *args)
{
	pthread_id = malloc(sizeof(pthread_t) * (args->number_of_philosophers + 1));
	if (!pthread_id)
	{
		// free(th->start);
		ft_free_forks(th[0].forks, args);
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
	ft_free_all(th, pthread_id);
	return (0);
}

int	main(int argc, char **argv)
{
	int			*start;
	t_args		*args;
	t_forks		*forks;
	t_thread	*th;

	if (argc < 5 || argc > 6)
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
	if (run(0, th, args))
		return (1);
	return (0);
}
