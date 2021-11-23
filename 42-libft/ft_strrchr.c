/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaplant <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 13:08:44 by llaplant          #+#    #+#             */
/*   Updated: 2021/05/10 14:48:22 by llaplant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	i;

	i = ft_strlen(str);
	if ((char)c == '\0')
		return ((char *)str + i);
	while (i--)
	{
		if (str[i] == (char)c)
			return ((char *)(str + i));
	}
	return (NULL);
}
