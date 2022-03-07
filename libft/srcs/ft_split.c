/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 17:35:33 by jihoh             #+#    #+#             */
/*   Updated: 2021/05/21 17:45:07 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**free_strs(char **strs)
{
	while (*strs)
	{
		free(*strs);
		strs++;
	}
	free(strs);
	return (NULL);
}

size_t	strs_size(const char *s, char c)
{
	size_t	size;

	size = 0;
	while (*s)
	{
		if (*s != c)
		{
			size++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (size);
}

char	*worddup(const char *s, char c)
{
	size_t			len;
	char			*ret;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	ret = (char *)ft_calloc(len + 1, sizeof(char));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s, len + 1);
	return (ret);
}

char	**ft_split(const char *s, char c)
{
	char			**strs;
	size_t			size;
	size_t			i;

	if (!s)
		return (NULL);
	size = strs_size(s, c);
	strs = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!strs)
		return (NULL);
	i = 0;
	while (i < size && *s)
	{
		if (*s != c)
		{
			strs[i++] = worddup(s, c);
			if (!strs)
				return (free_strs(strs));
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (strs);
}
