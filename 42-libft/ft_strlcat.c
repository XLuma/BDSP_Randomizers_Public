/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaplant <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:38:00 by llaplant          #+#    #+#             */
/*   Updated: 2021/05/10 11:38:23 by llaplant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;

	dstlen = ft_strlen(dest);
	srclen = ft_strlen(src);
	i = 0;
	if (dstlen < size)
		srclen += dstlen;
	else
	{
		srclen += size;
	}
	if (size > 0)
	{
		while (*(src + i) && (i + dstlen) < size - 1)
		{
			*(dest + i + dstlen) = *(src + i);
			i++;
		}
		*(dest + dstlen + i) = '\0';
	}
	return (srclen);
}
