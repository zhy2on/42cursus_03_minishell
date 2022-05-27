/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:57:37 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/27 22:12:58 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*join_converted_str(t_mini *mini, char *front, char *middle, char *back)
{
	char	*tmp;
	char	*replace_str;
	char	*ret;

	replace_str = NULL;
	tmp = NULL;
	if (*middle == - '$')
		replace_str = search_dollar_value(mini, middle);
	*middle = '\0';
	tmp = ft_strjoin(front, replace_str);
	ret = ft_strjoin(tmp, back);
	free(tmp);
	free(replace_str);
	return (ret);
}

char	*convert_str(t_mini *mini, char *str)
{
	char	*s;
	char	*front;
	char	*tmp;

	s = str;
	front = NULL;
	while (*s)
	{
		if (*s == - '$')
		{
			tmp = front;
			front = join_converted_str(mini, str, s, end_of_dollar(s));
			free(tmp);
			s = end_of_dollar(s);
			continue ;
		}
		s++;
	}
	if (!front)
		return (ft_strdup(str));
	return (front);
}
