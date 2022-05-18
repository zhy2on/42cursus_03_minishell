/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:41:26 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/18 15:29:45 by jihoh            ###   ########.fr       */
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
		if (parsing_line(str, mini) && syntax_check(mini, mini->tokens.first))
		{
			add_history(str);
			cmd = mini->tokens.first;
			if (!next_has_pipe(cmd))
				run_cmd(mini, cmd, create_args(cmd), 0);
			else
				run_cmd_with_pipe(mini, cmd);
		}
		free_token(&mini->tokens);
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

	ac = 0;
	av[1] = NULL;
	mini.envs.first = NULL;
	mini.tokens.first = NULL;
	mini.exit_code = 0;
	mini.fd.sd[0] = dup(STDIN);
	mini.fd.sd[1] = dup(STDOUT);
	while (*env)
		add_env(&mini.envs, ft_strdup(*env++));
	init_shlvl(&mini.envs);
	prompt(&mini);
	return (0);
}
