/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/02 13:19:16 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/09 13:52:17 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*result;

	result = s;
	i = 0;
	while (i < n)
	{
		result[i] = '\0';
		i++;
	}
}
