/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_write_error.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/02 18:39:20 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/09 00:02:57 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "functions.h"

int	ft_write_error(char *msg, int ret)
{
	write(2, msg, ft_strlen(msg));
	return (ret);
}
