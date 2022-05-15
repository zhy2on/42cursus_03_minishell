/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:43:18 by junyopar          #+#    #+#             */
/*   Updated: 2022/05/15 16:43:50 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
void    syntax_error(char *err)
{
	if  (!err)
		ft_putendl_fd(err,2);
}

int check_type(int type)
{
	if (type == HEREDOC || type == REDIROUT || type == REDIRIN \
	|| type == APPEND || type == PIPE)
		return (1);
	return (0);
}
int syntax_check(t_token *tokens)
{
	int ret;
	
	if (tokens != NULL && tokens->type == PIPE)
	{
		ft_putstr_fd("🐚minishell: syntax error near unexpected token ",2);
		ft_putstr_fd("`",2);
		ft_putstr_fd(tokens->str,2);
		ft_putendl_fd("'",2);     
		g_state.exit_status = 2;
		return (EXIT_FAILURE);
	}
	// while (tokens)
	// {
	// 	if (check_type(tokens->type))
	// 	{
	// 		ret = 
	// 	}
	// }
	return (1);
}
