/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaplant <llaplant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 10:27:32 by llaplant          #+#    #+#             */
/*   Updated: 2021/10/13 09:33:46 by llaplant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(char *str)
{
	long	sum;
	long	nop;

	sum = 0;
	nop = 1;
	while (*str == ' ' || *str == '\t'
		|| *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
	{
		str++;
	}
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
		{
			nop = nop * -1;
		}
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		sum = (sum * 10) + *str - '0';
		str++;
	}
	return (sum * nop);
}
