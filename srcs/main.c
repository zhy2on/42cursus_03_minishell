/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:41:26 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/15 02:11:25 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*next_cmd(t_token *ptr)
{
	while (ptr && ptr->type != PIPE)
		ptr = ptr->next;
	if (ptr)
		ptr = ptr->next;
	return (ptr);
}

char	**create_args(t_token *tokens, t_token *token)
{
	int		i;
	char	**ret;
	t_token	*ptr;

	i = 0;
	ptr = token;
	while (ptr && ptr->type != PIPE)
	{
		if (ptr->type <= ARG)
			i++;
		ptr = ptr->next;
	}
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	ptr = token;
	while (ptr && ptr->type != PIPE)
	{
		if (ptr->type <= ARG)
			ret[i++] = ptr->str;
		ptr = ptr->next;
	}
	ret[i] = NULL;
	return (ret);
}

void	eof_history(char *str)
{
	if (!str)
	{
		ft_putstr_fd("\033[1A", 1);
		ft_putstr_fd("🐚minishell$ ", 1);
		ft_putstr_fd("exit\n", 2);
		exit(EXIT_SUCCESS);
	}
	else
		add_history(str);
}

int	next_has_pipe(t_token *token)
{
	while (token && token->type != PIPE)
		token = token->next;
	if (!token)
		return (0);
	return (1);
}

void	run_cmd(t_mini *mini, t_token *cmd, char **args, int flag)
{
	handle_redirect(cmd, &mini->fd);
	if (builtin(&mini->envs, args) != SUCCESS)
		pre_exec(args, &mini->envs, flag);
	free(args);
}

void	run_cmd_with_pipe(t_mini *mini, t_token *cmd)
{
	char	**args;

	while (cmd)
	{
		args = create_args(&mini->tokens, cmd);
		pipe(mini->fd.pd);
		mini->pid = fork();
		if (mini->pid == 0)
		{
			if (next_has_pipe(cmd))
				dup2(mini->fd.pd[1], 1);
			run_cmd(mini, cmd, args, 1);
			exit(0);
		}
		else
		{
			dup2(mini->fd.pd[0], 0);
			close(mini->fd.pd[1]);
		}
		cmd = next_cmd(cmd);
	}
	while (waitpid(-1, 0, 0) > 0)
		;
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
		eof_history(str);
		if (parsing_line(str, mini) == SUCCESS)
		{
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

int	main(int ac, char **av, char **env)
{
	t_mini	mini;

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
