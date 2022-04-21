/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   take_forks.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/09 14:45:14 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/21 02:47:00 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_take_forks(t_philo *v)
{
	// if (v->id % 2)
	// 	usleep(400);
	// if (v->rules->number_of_philos % 2 && v->forks->last)
	// 	usleep(400);
	// if (v->id % 2 && !v->forks->last)
	// {
	// 	pthread_mutex_lock(&v->forks->value_m);
	// 	pthread_mutex_lock(&v->forks->next->value_m);
	// }
	// else
	// {
	// 	pthread_mutex_lock(&v->forks->next->value_m);
	// 	pthread_mutex_lock(&v->forks->value_m);
	// }
	// if (!v->forks->in_use && !v->forks->next->in_use)
	// {
	// 	pthread_mutex_lock(&v->stop_m);
	// 	if (v->stop == 0)
	// 		printf("%lims %i has taken %sfork%s\n", get_time() - v->time.first_timestamp, v->id, KRED, KWHT);
	// 	v->forks->in_use = 1;
	// 	if (v->stop == 0)
	// 		printf("%lims %i has taken %sfork%s\n", get_time() - v->time.first_timestamp, v->id, KRED, KWHT);
	// 	v->forks->next->in_use = 1;
	// 	pthread_mutex_unlock(&v->stop_m);
	// 	pthread_mutex_unlock(&v->forks->value_m);
	// 	pthread_mutex_unlock(&v->forks->next->value_m);
	// 	return (0);
	// }
	// pthread_mutex_unlock(&v->forks->value_m);
	// pthread_mutex_unlock(&v->forks->next->value_m);
	// usleep(400);


	while (1)
	{
		pthread_mutex_lock(v->right_val);
		if (*v->right_in_use == 0)
		{
			*v->right_in_use = 1;
			pthread_mutex_unlock(v->right_val);
			printf("%lims %i has taken %sfork%s\n", get_time() - v->time.first_timestamp, v->id, KRED, KWHT);
			break ;
		}
		pthread_mutex_unlock(v->right_val);
		usleep(100);
		if (ft_stop(v))
			return (1);
	}
	while (1)
	{
		pthread_mutex_lock(v->left_val);
		if (*v->left_in_use == 0)
		{
			*v->left_in_use = 1;
			pthread_mutex_unlock(v->left_val);
			printf("%lims %i has taken %sfork%s\n", get_time() - v->time.first_timestamp, v->id, KRED, KWHT);
			return (0);
		}
		pthread_mutex_unlock(v->left_val);
		usleep(100);
		if (ft_stop(v))
			return (1);
	} 
	// pthread_mutex_lock(v->right);
	// printf("%lims %i has taken %sfork%s\n", get_time() - v->time.first_timestamp, v->id, KRED, KWHT);
	// pthread_mutex_lock(v->left);
	// printf("%lims %i has taken %sfork%s\n", get_time() - v->time.first_timestamp, v->id, KRED, KWHT);
	// return (0);


	// while (1)
	// {
	// 	pthread_mutex_lock(&v->stop_m);
	// 	if (v->stop == 1)
	// 	{
	// 		pthread_mutex_unlock(&v->stop_m);
	// 		return (1);
	// 	}
	// 	pthread_mutex_unlock(&v->stop_m);
	// 	pthread_mutex_lock(v->right_val);
	// 	if (*v->right_in_use)
	// 	{
	// 		pthread_mutex_unlock(v->right_val);
	// 		usleep(200);
	// 		continue;
	// 	}
	// 	pthread_mutex_lock(v->left_val);
	// 	if (*v->left_in_use == 0 && *v->right_in_use == 0)
	// 	{
	// 		pthread_mutex_lock(v->right);
	// 		printf("%lims %i has taken %sfork%s\n", get_time() - v->time.first_timestamp, v->id, KRED, KWHT);
	// 		pthread_mutex_lock(v->left);
	// 		printf("%lims %i has taken %sfork%s\n", get_time() - v->time.first_timestamp, v->id, KRED, KWHT);
	// 		*v->left_in_use = 1;
	// 		*v->right_in_use = 1;
	// 		pthread_mutex_unlock(v->right_val);
	// 		pthread_mutex_unlock(v->left_val);
	// 		return (0);
	// 	}
	// 	pthread_mutex_unlock(v->right_val);
	// 	pthread_mutex_unlock(v->left_val);
	// 	usleep(200);
	// }
	// // pthread_mutex_unlock(&v->stop_m);
}
