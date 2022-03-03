/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/03 14:42:23 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/03/03 16:49:19 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>//gettimeofday
#include <stdio.h>//printf
#include <unistd.h>//sleep
#include <stdlib.h>
#include <pthread.h>
  
pthread_mutex_t mutex;

struct arg_struct {
    int id;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
};

struct forks {
    int id;
	int	in_use;
};

void	*philo(void *var)
{
	int i = 5;
	struct arg_struct *args = (struct arg_struct *)var;
	pthread_mutex_lock(&mutex);
	while (i)
	{
		printf("%i. this is in a thread\n", args->id);
		i--;
	}
	pthread_mutex_unlock(&mutex);
	return (0);
}

int main(int argc, char **argv)
{
	int i = 0;
	int number_of_philosophers = 5;
	
	pthread_t pthread_id;
	struct arg_struct *list;
	struct forks *forks;


    // if (argc != 6)
	// {
	// 	printf("Usage ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]]");
	// 	exit(1);
	// }
	pthread_mutex_init(&mutex, 0);
	list = malloc(sizeof(struct arg_struct) * number_of_philosophers);
	if (!list)
		exit(1);
	forks = malloc(sizeof(struct forks) * number_of_philosophers);
	if (!forks)
		exit(1);
	for (int j = 0; j < number_of_philosophers; j++)
	{
		forks[j].id = j;
		forks[j].in_use = 0;
	}
	for (int j = 0; j < number_of_philosophers; j++)
		list[j].id = j;
	while (i < number_of_philosophers)
	{
		pthread_create(&pthread_id, 0, &philo, &list[i]);
		i++;
	}
	pthread_join(pthread_id, 0);
	pthread_mutex_destroy(&mutex);
	pthread_detach(pthread_id);
    return 0;
}
