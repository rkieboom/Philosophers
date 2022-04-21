/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/08 16:37:19 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/21 18:08:58 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

int	parse(t_list *v, char **argv)
{
	t_rules	*rules;

	rules = ft_calloc(1, sizeof(t_rules));
	if (!rules)
		return (ft_write_error("Error, malloc failed!\n", 1));
	rules->number_of_philos = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		rules->amount_of_times_to_eat = ft_atoi(argv[5]);
	else
		rules->amount_of_times_to_eat = -1;
	v->rules = rules;
	return (0);
}
