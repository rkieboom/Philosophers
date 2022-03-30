/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/06 12:45:06 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/03/06 12:48:49 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	struct timeval time, time2;
	gettimeofday(&time, 0);//start???

	usleep(200);
	
	gettimeofday(&time2, 0);//start???

	printf("%d\n", time2.tv_usec - time.tv_usec);
	


	return (0);
}