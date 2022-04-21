/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isdigit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/02 16:19:19 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/21 18:07:45 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isdigit_s(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit_s(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
