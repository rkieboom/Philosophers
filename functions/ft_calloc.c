/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/06 15:10:13 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/02 15:26:48 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*result;

	i = 0;
	result = (char *)malloc(sizeof(char) * (count * size));
	if (result == NULL)
		return (NULL);
	while (i != (count * size))
	{
		result[i] = 0;
		i++;
	}
	return (result);
}
