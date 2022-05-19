/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:41:26 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/19 18:51:59 by jihoh            ###   ########.fr       */
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
		if (parsing_line(str, mini) && syntax_check(mini, mini->tokens))
		{
			add_history(str);
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

void	init_shlvl(t_env **penvs)
{
	t_env	*shlvl;
	char	*value;

	shlvl = search_env(*penvs, "SHLVL");
	value = ft_itoa(ft_atoi(shlvl->value) + 1);
	add_env(penvs, ft_strjoin("SHLVL=", value));
	free(value);
}

int	main(int ac, char **av, char **env)
{
	t_mini	mini;
	t_env	*ptr;

	ac = 0;
	av[1] = NULL;
	mini.envs = NULL;
	mini.tokens = NULL;
	mini.exit_code = 0;
	mini.fd.sd[0] = dup(STDIN);
	mini.fd.sd[1] = dup(STDOUT);
	while (*env)
		add_env(&mini.envs, ft_strdup(*env++));
	ptr = mini.envs;
	init_shlvl(&mini.envs);
	prompt(&mini);
	return (0);
}
