/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   functions.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/08 16:52:57 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/21 18:07:59 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "../header.h"

int			ft_atoi(const char *str);
long long	ft_atoi_l(const char *str);
void		*ft_calloc(size_t count, size_t size);
int			ft_isdigit(char *str);
size_t		ft_strlen(const char *str);
int			ft_write_error(char *msg, int ret);
long		get_time(void);
void		ft_bzero(void *s, size_t n);

#endif