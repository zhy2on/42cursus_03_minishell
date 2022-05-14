/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:41:26 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/15 04:21:51 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prompt(t_mini *mini)
{
	char	*str;
	t_token	*cmd;

	while (1)
	{
		set_signal();
		restore_inout(&mini->fd);
		str = readline("🐚minishell$ ");
		if (parsing_line(str, mini) == SUCCESS)
		{
			add_history(str);
			cmd = mini->tokens.first;
			if (!next_has_pipe(cmd))
				run_cmd(mini, cmd, create_args(&mini->tokens, cmd), 0);
			else
				run_cmd_with_pipe(mini, cmd);
			free_token(&mini->tokens);
		}
		free(str);
	}
}

void	init_shlvl(t_env *envs)
{
	t_env	*shlvl;
	char	*value;

	shlvl = search_env(envs, "SHLVL");
	value = ft_itoa(ft_atoi(shlvl->value) + 1);
	add_env(envs, ft_strjoin("SHLVL=", value));
	free(value);
}

int	main(int ac, char **av, char **env)
{
	t_mini	mini;
	t_env	*shlvl;

	mini.envs.first = NULL;
	mini.tokens.first = NULL;
	mini.fd.sd[0] = dup(STDIN);
	mini.fd.sd[1] = dup(STDOUT);
	while (*env)
		add_env(&mini.envs, ft_strdup(*env++));
	init_shlvl(&mini.envs);
	prompt(&mini);
	return (0);
}
