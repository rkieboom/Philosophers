/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/08 16:34:41 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/21 17:29:07 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void free_mutexes(t_list *v)
{
	int	i;

	i = 0;
	while (i < v->rules->number_of_philos)
	{
		pthread_mutex_destroy(&v->forks_val[i]);
		pthread_mutex_destroy(&v->ph[i].eat_count_m);
		pthread_mutex_destroy(&v->ph[i].time.mutex);
		pthread_mutex_destroy(&v->ph[i].stop_m);
		i++;
	}
}

static void	free_all(t_list *v)
{
	free_mutexes(v);
	free(v->rules);
	free(v->ph);
	free(v->forks_val);
	free(v->in_use);
}

int	main(int argc, char **argv)
{
	t_list v;

	ft_bzero(&v, sizeof(t_list));
	if (lexer(argc, argv) || parse(&v, argv))
		return (1);
	if (init_forks(&v))
		return (2);
	if (setup_philos(&v))
		return (3);
	if (create_and_start_threads(&v))
		return (4);
	free_all(&v);
	return (0);
}
