/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:41:26 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/29 13:49:50 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prompt(t_mini *mini)
{
	char	*str;

	while (1)
	{
		init_inout(mini);
		init_fd(mini);
		set_signal();
		str = readline("minishell$ ");
		if (str && *str)
			add_history(str);
		if (parsing_line(str, mini) && syntax_check(mini, mini->tokens))
			run_cmd_line(mini, mini->tokens, NULL);
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
