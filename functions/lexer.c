/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/08 16:36:14 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/09 00:40:49 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

static int	lexer2(char **argv)
{
	int	i;
	int	temp;

	i = 2;
	temp = ft_atoi(argv[1]);
	if (temp < 1 || temp > 200)
		return (ft_write_error("Keep amount of philosophers between 1-200!\n", 1));
	while (i < 5)
	{
		temp = ft_atoi(argv[i]);
		if (temp < 60)
			return (ft_write_error("Keep the milliseconds 60 or above!\n", 1));
		i++;
	}
	return (0);
}

int			lexer(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("usage ./philo amount_of_philos time_to_die time_to_eat time_to_sleep [amount_of_times_to_eat]\n");
		return (1);
	}
	while (argv[i])
	{
		if (ft_isdigit(argv[i]) == 0)
			return (ft_write_error("Negative or non numeric value!\n", 1));
		if (ft_atoi(argv[i]) != ft_atoi_l(argv[i]))
			return (ft_write_error("Overflowing number!\n", 1));
		if (ft_atoi(argv[i]) == -1)
			return (ft_write_error("Overflowing number!\n", 1));
		i++;
	}
	if (lexer2(argv))
		return (1);
	return (0);
}
