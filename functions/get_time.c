/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_time.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/02 11:59:08 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/03 13:23:46 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stddef.h>

long	get_time(void)
{
	struct timeval	tp;
	long			milliseconds;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	return (milliseconds);
}
