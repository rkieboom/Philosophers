/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/03 14:42:23 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/02 17:42:50 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>//gettimeofday
#include <stdio.h>//printf
#include <unistd.h>//sleep
#include <stdlib.h>
#include <pthread.h>

#include "header.h"

int main(int argc, char **argv)
{
	int i = 0;
	if (argc < 4)
	{
		dprintf(2, "Usage ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep]\n");
		return (1);
	}
	
	int	*start = calloc(1, sizeof(int));
	t_args *args = malloc(sizeof(t_args));
	args->number_of_philosophers = atoi(argv[1]);
	args->time_to_die = atoi(argv[2]);
	args->time_to_eat = atoi(argv[3]);
	args->time_to_sleep = atoi(argv[4]);
	
	pthread_t *pthread_id = malloc(sizeof(pthread_t) * (args->number_of_philosophers + 1));

	t_forks	*forks;

	//Create linked list forks
	for(int i = 0; i < args->number_of_philosophers; i++)
	{
		if (i == 0)
			forks = fork_create();
		else if (i + 1 == args->number_of_philosophers)
			fork_add_back_last(&forks, fork_create());
		else
			fork_add_back(&forks, fork_create());
	}
	t_forks	*temp = forks;
	t_thread *th = calloc(args->number_of_philosophers, sizeof(t_thread));
	if (!th)
		return (1);
	for (int i = 0; i < args->number_of_philosophers; i++)
	{
		th[i].id = i + 1;
		th[i].forks = temp;
		th[i].values = args;
		th[i].start = start;
		pthread_mutex_init(&temp->mutex, 0);
		temp = temp->right;
	}
	th[0].forks->left = fork_last(th[0].forks);

	while (i < args->number_of_philosophers)
	{
		pthread_create(&pthread_id[i], 0, &philosophers, &th[i]);
		i++;
	}
	pthread_create(&pthread_id[args->number_of_philosophers], 0, &monitoring_thread, th);
	for (int i = 0; i < args->number_of_philosophers + 1; i++)
		pthread_join(pthread_id[i], 0);
	temp = forks;
	for (int i = 0; i < args->number_of_philosophers; i++)
	{
		pthread_mutex_destroy(&temp->mutex);
		temp = temp->right;
	}
	return 0;
}
