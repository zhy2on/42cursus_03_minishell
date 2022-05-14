/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:41:26 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/14 22:01:13 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**create_args(t_token *tokens, t_token **pptr)
{
	int		i;
	char	**ret;
	t_token	*ptr;

	i = 0;
	ptr = *pptr;
	while (ptr && ptr->type != PIPE)
	{
		if (ptr->type <= ARG)
			i++;
		ptr = ptr->next;
	}
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	ptr = *pptr;
	while (ptr && ptr->type != PIPE)
	{
		if (ptr->type <= ARG)
			ret[i++] = ptr->str;
		ptr = ptr->next;
	}
	ret[i] = NULL;
	*pptr = ptr;
	return (ret);
}

int	parsing_cmd(char *str, t_mini *mini)
{
	int		i;
	char	quot;
	t_token	*tmp;

	i = 0;
	quot = '\0';
	if (parsing_line(str, mini) == ERROR)
		return (ERROR);
	tmp = mini->tokens.first;
	while (tmp)
	{
		printf("%d %s\n", tmp->type, tmp->str);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

void	eof_history(char *str)
{
	if (str == NULL)
	{
		ft_putstr_fd("\033[1A", 1);
		ft_putstr_fd("🐚minishell$ ", 1);
		ft_putstr_fd("exit\n", 2);
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (ft_strcmp(str, "exit") == 0)
		{
			ft_putendl_fd("exit", 2);
			free(str);
			exit(EXIT_SUCCESS);
		}
		add_history(str);
	}
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
	return ;
}

void	handle_tokens(t_mini *mini, char **env)
{
	t_token	*cmd;
	t_token	*ptr;
	char	**args;

	ptr = mini->tokens.first;
	if (!next_has_pipe(ptr))
	{
		cmd = ptr;
		args = create_args(&mini->tokens, &ptr);
		run_cmd(mini, cmd, args, 0);
		return ;
	}
	while (ptr)
	{
		if (ptr->type == PIPE)
		{
			ptr = ptr->next;
			continue ;
		}
		cmd = ptr;
		args = create_args(&mini->tokens, &ptr);
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
	}
	while (waitpid(-1, 0, 0) > 0)
		;
}

void	prompt(t_mini *mini, char **env)
{
	char	*str;

	while (1)
	{
		set_signal();
		restore_inout(&mini->fd);
		str = readline("🐚minishell$ ");
		eof_history(str);
		if (!*str)
		{
			free(str);
			continue ;
		}
		mini->tokens.first = NULL;
		if (parsing_cmd(str, mini) == ERROR)
			continue ;
		handle_tokens(mini, env);
		free_token(&mini->tokens);
		free(str);
	}
}

int	main(int ac, char **av, char **env)
{
	t_mini	mini;
	int		i;

	i = 0;
	mini.envs.first = NULL;
	mini.fd.sd[0] = dup(STDIN);
	mini.fd.sd[1] = dup(STDOUT);
	while (env[i])
		add_env(&mini.envs, ft_strdup(env[i++]));
	init_shlvl(&mini.envs);
	prompt(&mini, env);
	return (0);
}
