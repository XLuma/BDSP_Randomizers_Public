/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaplant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 12:29:15 by llaplant          #+#    #+#             */
/*   Updated: 2021/05/18 17:15:37 by llaplant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	int_len(long n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		n = n * -1;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*convert(char *tmp, long n, int len)
{
	if (n < 0)
	{
		tmp[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		tmp[len] = '0' + (n % 10);
		n = n / 10;
		len--;
	}
	return (tmp);
}

char	*ft_itoa(int n)
{
	int		i;
	long	nb;
	char	*tmp;

	nb = n;
	i = int_len(nb);
	if (i == 0)
		i = 1;
	tmp = (char *)malloc(sizeof(char) * (i + 1));
	if (!tmp)
		return (NULL);
	tmp[i--] = '\0';
	if (n == 0)
	{
		tmp[0] = '0';
		tmp[1] = '\0';
		return (tmp);
	}
	tmp = convert(tmp, nb, i);
	return (tmp);
}
