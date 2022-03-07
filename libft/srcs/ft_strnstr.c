/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 16:44:12 by jihoh             #+#    #+#             */
/*   Updated: 2021/05/22 14:52:05 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *h, const char *n, size_t len)
{
	size_t	i;
	size_t	j;

	if (!n[0])
		return ((char *)h);
	i = 0;
	while (h[i] && i < len)
	{
		j = 0;
		while ((h[i + j] == n[j]) && (i + j < len))
		{
			j++;
			if (!n[j])
				return ((char *)h + i);
		}
		i++;
	}
	return (NULL);
}
