/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:41:26 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/12 21:34:52 by jihoh            ###   ########.fr       */
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
		// ft_putstr_fd("\033[1A",2);
		// ft_putstr_fd("\033[6C",2);
		ft_putstr_fd("\033[15D",1);
		ft_putstr_fd("🐚minishell$ ",1);
		ft_putstr_fd("exit\n",2);
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (ft_strcmp(str, "exit") == 0)
		{
			ft_putendl_fd("exit",2);
			free(str);
			exit(EXIT_SUCCESS);
		}
		add_history(str);
	}
}

void	handle_tokens(t_mini *mini, char **env)
{
	t_token	*ptr;
	char	**args;
	t_fd	fd;

	ptr = mini->tokens.first;
	while (ptr)
	{
		handle_redirect(ptr, &fd);
		args = create_args(&mini->tokens, &ptr);
		if (builtin(&mini->envs, args) != SUCCESS)
			test_exec(args, &mini->envs, &mini->tokens);
		free(args);
		restore_inout(&mini->fd);
	}
}

void	prompt(t_mini *mini, char **env)
{
	char	*str;

	// set_signal();
	while (1)
	{
		str = readline("🐚minishell$ ");
		//eof_history(str);
		if (!*str)
			continue ;
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
	mini.fd.in = dup(STDIN);
	mini.fd.out = dup(STDOUT);
	mini.fd.fdout = -1;
	while (env[i])
		add_env(&mini.envs, env[i++]);
	init_shlvl(&mini.envs);
	prompt(&mini, env);
	return (0);
}
