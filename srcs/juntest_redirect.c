/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:23:28 by junyopar          #+#    #+#             */
/*   Updated: 2022/05/09 19:23:29 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"
// pipex.ver
int	redirect_in(char *file)
{
	g_data.redir_in = open(file, O_RDONLY);
	if (g_data.redir_in < 0)
	{
		fprintf(stderr,"test message\n");
		g_data.exit_status = 1;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	redirect_out(char *file)
{
	g_data.redir_out = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (g_data.redir_out < 0)
	{
		// print_errmsg(file, strerror(errno));
		g_data.exit_status = 1;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
int
	redirect_out_append(char *file)
{
	g_data.redir_out = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (g_data.redir_out < 0)
	{
		// print_errmsg(file, strerror(errno));
		g_data.exit_status = 1;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
