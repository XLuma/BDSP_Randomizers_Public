/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luma <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 12:41:13 by luma              #+#    #+#             */
/*   Updated: 2021/05/04 14:41:20 by luma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*st2;
	size_t	i;

	st2 = (char *)dest;
	i = 0;
	while (i < n)
	{
		*(char *)st2 = *(char *)src;
		src++;
		st2++;
		i++;
	}
	return (dest);
}
