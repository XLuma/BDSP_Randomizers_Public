/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaplant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 09:50:48 by llaplant          #+#    #+#             */
/*   Updated: 2021/05/10 10:12:14 by llaplant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*tmp1;
	char		*tmp2;
	size_t		i;

	tmp1 = (const char *)src;
	tmp2 = (char *)dest;
	i = 0;
	if (tmp2 < tmp1)
	{
		while (i < n)
		{
			tmp2[i] = tmp1[i];
			i++;
		}
	}
	else
	{
		while (n-- > 0)
		{
			tmp2[n] = tmp1[n];
		}
	}
	return (dest);
}
