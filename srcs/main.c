/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:41:26 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/20 19:49:07 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prompt(t_mini *mini)
{
	char	*str;
	t_token	*cmd;

	while (1)
	{
		init_inout(mini);
		init_fd(mini);
		set_signal();
		str = readline("🐚minishell$ ");
		if (str && *str)
			add_history(str);
		if (parsing_line(str, mini) && syntax_check(mini, mini->tokens))
		{
			cmd = mini->tokens;
			if (!next_has_pipe(cmd))
				run_cmd(mini, cmd, create_args(cmd), 0);
			else
				run_cmd_with_pipe(mini, cmd);
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
