/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaplant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 10:59:38 by llaplant          #+#    #+#             */
/*   Updated: 2021/05/11 16:56:30 by llaplant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	verify_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set++)
		{
			return (1);
		}
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*s2;
	int		j;

	i = 0;
	j = 0;
	s2 = (char *)malloc(sizeof(s2) * (ft_strlen(s1) + 1));
	if (!s2)
		return (NULL);
	while (verify_set(s1[i], set) == 1)
		i++;
	while (s1[i])
		s2[j++] = s1[i++];
	while (verify_set(s2[j - 1], set) == 1)
		j--;
	s2[j] = '\0';
	return (s2);
}
