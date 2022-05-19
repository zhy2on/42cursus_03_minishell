/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:41:26 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/20 01:47:17 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	restore_inout(t_fd *fd)
{
	dup2(fd->sd[0], STDIN);
	dup2(fd->sd[1], STDOUT);
}

void	run_cmd(t_mini *mini, t_token *cmd, char **args, int flag)
{
	if (!handle_redirect(mini, cmd))
		return ;
	if (!builtin(mini, args))
		pre_exec(mini, args, flag);
	free(args);
}

void	prompt(t_mini *mini)
{
	char	*str;
	t_token	*cmd;

	while (1)
	{
		set_signal();
		restore_inout(&mini->fd);
		str = readline("🐚minishell$ ");
		if (!*str)
			continue ;
		add_history(str);
		if (parsing_line(str, mini) && syntax_check(mini, mini->tokens))
		{
			cmd = mini->tokens;
			if (!next_has_pipe(cmd))
				run_cmd(mini, cmd, create_args(cmd), 0);
			else
				run_cmd_with_pipe(mini, cmd);
			printf("%d %d\n", mini->fd.pd[0], mini->fd.pd[1]);
		}
		free_token(&mini->tokens);
		free(str);
	}
}

int	main(int ac, char **av, char **env)
{
	t_mini	mini;
	t_env	*ptr;

	ac = 0;
	av[1] = NULL;
	init_mini(&mini);
	while (*env)
		add_env(&mini.envs, ft_strdup(*env++));
	ptr = mini.envs;
	init_shlvl(&mini.envs);
	prompt(&mini);
	return (0);
}
