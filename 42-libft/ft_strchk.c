/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaplant <llaplant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 13:29:38 by llaplant          #+#    #+#             */
/*   Updated: 2021/09/08 09:38:13 by llaplant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*ft_strchk: function to verify if
 * there are any other characters in
 * a string other than the characters
 * in the specified charset.
 * returns zero if only chars from the
 * charset are present, returns 1 otherwise*/

#include "libft.h"

int	ft_strchk(char *str, char *charset)
{
	int	i;
	int	j;
	int	charset_len;

	i = 0;
	j = 0;
	charset_len = ft_strlen(charset);
	while (str[i])
	{
		while (charset[j])
		{
			if (str[i] == charset[j])
				break ;
			else
				j++;
		}
		if (j == charset_len)
			return (1);
		j = 0;
		i++;
	}
	return (0);
}
