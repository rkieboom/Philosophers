/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/08 16:34:41 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/09 13:55:05 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	free_all(t_list *v)
{
	if (v->rules)
		free(v->rules);
	if (v->forks)
		freeforks(v->forks);
	if (v->ph)
		free(v->ph);
}

int	main(int argc, char **argv)
{
	t_list v;

	ft_bzero(&v, sizeof(t_list));
	if (lexer(argc, argv) || parse(&v, argv))
		return (1);
	if (init_forks(&v, 0))
		return (2);
	if (setup_philos(&v))
		return (3);
	if (create_and_start_threads(&v))
		return (4);
	free_all(&v);
	return (0);
}
