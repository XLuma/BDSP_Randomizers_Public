/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaplant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 11:08:22 by llaplant          #+#    #+#             */
/*   Updated: 2021/05/10 10:10:52 by llaplant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	chr;

	s = (unsigned char *)str;
	chr = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (s[i] == chr)
		{
			return (s + i);
		}
		i++;
	}
	return (NULL);
}
