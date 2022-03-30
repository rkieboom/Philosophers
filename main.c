/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/03 14:42:23 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/03/30 20:01:12 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>//gettimeofday
#include <stdio.h>//printf
#include <unistd.h>//sleep
#include <stdlib.h>
#include <pthread.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#include "header.h"

long	get_time(void)
{
	struct timeval	tp;
	long			milliseconds;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	return (milliseconds);
}

int		check_if_dead(t_thread *args, long start)
{
	// printf("Start = [%li]\nEnd = [%li]\n", args->forks->start, get_time() - args->forks->start);
	// printf("time_to_die = [%li]\n", args->values->time_to_die);
	if (get_time() - start > args->values->time_to_die)
		return (1);
	return (0);
}

void	ft_sleep(t_thread *v, long first_timestamp)
{
	while (get_time() - first_timestamp < v->values->time_to_sleep)
		usleep(2000);
	// printf("%li", get_time() - first_timestamp);
}

void	ft_eat(t_thread *v, long first_timestamp)
{
	while (get_time() - first_timestamp < v->values->time_to_eat)
		usleep(1000);
	// printf("%li", get_time() - first_timestamp);
}

void	*philo(void *var)
{
	long			start;
	long			timestamp;
	t_thread *args = (t_thread *)var;
	if (!args)
	{
		dprintf(2, "Something happend!");
		return (0);
	}
	start = get_time();
	timestamp = start;
	while (1)
	{
		if (check_if_dead(args, timestamp))
		{
			printf("%i. %li/%lims died!\n", args->id, get_time() - start, get_time() - start);
			break ;
		}
		while (1)
		{
			if (args->forks->in_use == 0 && args->forks->right->in_use == 0)
			{
				args->forks->in_use = 1;
				args->forks->right->in_use = 1;
				break ;
			}
			usleep(100);
		}
		pthread_mutex_lock(&args->forks->mutex);
		pthread_mutex_lock(&args->forks->right->mutex);
		if (check_if_dead(args, timestamp))
		{
			printf("%i. %li/%lims died!\n", args->id, get_time() - start, get_time() - start);
			// pthread_mutex_unlock(&args->forks->mutex);
			// pthread_mutex_unlock(&args->forks->right->mutex);
			break ;
		}
		printf("%li/%lims %i has taken %sfork%s\n", get_time() - start, get_time() - timestamp, args->id, KBLU, KWHT); //take forks
		if (check_if_dead(args, timestamp))
		{
			printf("%i. %li/%lims died!\n", args->id, get_time() - start, get_time() - start);
			// pthread_mutex_unlock(&args->forks->mutex);
			// pthread_mutex_unlock(&args->forks->right->mutex);
			break ;
		}
		// ft_sleep(timestamp);
		printf("%li/%lims %i is %seating%s\n", get_time() - start, get_time() - timestamp, args->id, KGRN, KWHT); //eat
		// start = get_time();
		timestamp = get_time();
		usleep(args->values->time_to_eat * 1000);
		pthread_mutex_unlock(&args->forks->right->mutex);
		pthread_mutex_unlock(&args->forks->mutex);
		args->forks->in_use = 0;
		args->forks->right->in_use = 0;
		printf("%li/%lims %i is %ssleeping%s\n", get_time() - start, get_time() - timestamp, args->id, KRED, KWHT);//sleep
		usleep(args->values->time_to_sleep * 1000);
		if (check_if_dead(args, timestamp))
		{
			printf("%i. %li/%lims died!\n", args->id, get_time() - start, get_time() - start);
			// pthread_mutex_unlock(&args->forks->mutex);
			// pthread_mutex_unlock(&args->forks->right->mutex);
			break ;
		}
		printf("%li/%lims %i is thinking\n", get_time() - start, get_time() - timestamp, args->id);//think

	}
	int *ret = ft_calloc(1, sizeof(int));
	*ret = args->id;
	return ((void*)ret);
}

int main(int argc, char **argv)
{
	int i = 0;
	if (argc < 4)
	{
		dprintf(2, "Usage ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep]\n");
		return (1);
	}
	
	
	t_args *args = malloc(sizeof(t_args));
	args->number_of_philosophers = atoi(argv[1]);
	args->time_to_die = atoi(argv[2]);
	args->time_to_eat = atoi(argv[3]);
	args->time_to_sleep = atoi(argv[4]);
	
	pthread_t *pthread_id = malloc(sizeof(pthread_t) * (args->number_of_philosophers));

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
		th[i].id = i;
		th[i].forks = temp;
		th[i].values = args;
		th[i].pthread_id = pthread_id;
		pthread_mutex_init(&temp->mutex, 0);
		temp = temp->right;
	}
	while (i < args->number_of_philosophers)
	{
		pthread_create(&pthread_id[i], 0, &philo, &th[i]);
		i++;
	}
	int	*ret;
	// int **ret = ft_calloc(args->number_of_philosophers, sizeof(int *));
	// for (int i = 0; i < args->number_of_philosophers; i++)
	// 	ret[i] = ft_calloc(1, sizeof(int));
	for (int i = 0; i < args->number_of_philosophers; i++)
		pthread_join(pthread_id[i], (void*)&ret);
	printf("%i. has died!\n", *ret);\
	exit(EXIT_SUCCESS);
	temp = forks;
	for (int i = 0; i < args->number_of_philosophers; i++)
	{
		pthread_mutex_destroy(&temp->mutex);
		temp = temp->right;
	}
	return 0;
}
