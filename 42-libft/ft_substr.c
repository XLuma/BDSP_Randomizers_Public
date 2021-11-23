/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaplant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 10:02:09 by llaplant          #+#    #+#             */
/*   Updated: 2021/05/13 14:39:21 by llaplant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*cut;

	i = 0;
	if (ft_strlen(s) < start)
	{
		cut = (char *)malloc(sizeof(char));
		if (!cut)
			return (NULL);
		*cut = '\0';
		return (cut);
	}
	cut = malloc(sizeof(char) * len + 1);
	if (!cut)
		return (NULL);
	while (i < len)
	{
		cut[i] = s[start];
		i++;
		start++;
	}
	cut[i] = '\0';
	return (cut);
}
