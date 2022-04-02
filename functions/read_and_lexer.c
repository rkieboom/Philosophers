/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_and_lexer.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/02 18:41:00 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/02 19:49:04 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int	only_nums(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	lexer(t_args *args, char **argv)
{
	int	i;

	i = 1;
	if (argv[5])
		args->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	if (argv[5] && ft_atoi(argv[5]) != ft_atoi_l(argv[5]))
		return (ft_write_error("Error, overflowing number!\n", 1));
	while (argv[i])
	{
		if (only_nums(argv[i]))
			return (ft_write_error("Error, Non numeric charachters or -\n", 1));
		i++;
	}
	if (args->number_of_philosophers < 0 || \
	args->number_of_times_each_philosopher_must_eat < 0 \
	|| args->time_to_die < 0 || args->time_to_eat < 0 \
	|| args->time_to_sleep < 0)
		return (ft_write_error("Error, overflowing number!\n", 1));
	return (0);
}

t_args	*read_and_lexer(t_args *args, char **argv)
{
	args = ft_calloc(1, sizeof(t_args));
	if (!args)
		return (0);
	args->number_of_philosophers = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if ((ft_atoi(argv[1]) != ft_atoi_l(argv[1])) || \
	(ft_atoi(argv[2]) != ft_atoi_l(argv[2])) \
	|| (ft_atoi(argv[3]) != ft_atoi_l(argv[3])) || \
	(ft_atoi(argv[4]) != ft_atoi_l(argv[4])))
	{
		ft_write_error("Error, overflowing number!\n", 0);
		free(args);
		return (0);
	}
	if (lexer(args, argv))
	{
		free(args);
		return (0);
	}
	return (args);
}
