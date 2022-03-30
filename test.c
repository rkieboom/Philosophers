/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/06 12:45:06 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/03/30 20:33:43 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

static void	*philo(void *var)
{
	int *id = (int*)var;
	int *ret = malloc(sizeof(int));
	*ret = *id;
	printf("im id=[%i]\n", *id);
	return ((void*)ret);
}

int main(void)
{
	int **ret;
	pthread_t pthread_id[3];
	
	ret = malloc(sizeof(int*) * 3);
	for (int i = 0; i < 3; i++)
		pthread_create(&pthread_id[i], 0, &philo, (void*)&i);

	for (int i = 0; i < 3; i++)
		pthread_join(pthread_id[i], (void*)&ret[i]);
	
	printf("ret = [%i]", *ret[2]);
	free(ret);

	return (0);
}