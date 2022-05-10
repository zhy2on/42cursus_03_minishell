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
void	redirect_in(const char *file)
{
	int	infile;

	infile = open(file, O_RDONLY);
	if (infile < 0)
	{
		perror("open fail");
		exit(1);
	}
	dup2(infile, STDIN_FILENO);
	close(infile);
}

void	redirect_out(const char *file)
{
	int	outfile;

	outfile = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (outfile < 0)
	{
		perror("open fail\n");
		exit(1);
	}
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
}