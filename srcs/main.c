/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:41:26 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/03 16:51:01 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parsing_cmd(char *str, t_token *tokens)
{
	int		i;
	char	quot;
	t_token	*tmp;

	i = 0;
	quot = '\0';
	parsing_line(str, &quot, tokens, i);
	tmp = tokens->first;
	while (tmp)
	{
		printf("%d %s\n", tmp->type, tmp->str);
		tmp = tmp->next;
	}
	if (quot)
	{
		fprintf(stderr,"minishell: single quotate error\n");
		return (ERROR);
	}
	return (SUCCESS);
}

void	prompt(t_env *envs,char **env)
{
	char	*str;
	char	**args;
	t_token	*tokens;
	int		i;

	// env_print(env);
	// rl_catch_signals = 0;
	set_signal();
	while (1)
	{
		args = (char **)malloc(sizeof(char *) * ARG_MAX);
		tokens = (t_token *)malloc(sizeof(t_token));
		str = readline("🐚minishell$ ");
		add_history(str);
		if (parsing_cmd(str, tokens) == ERROR)
			continue ;
		/*
		if (builtin(envs, args) == SUCCESS)
			continue ;
		else
			exec(args);
		*/
		free(tokens);
		free(args);
		free(str);
	}
}

static void	print_envs(t_env *envs)
{
	int i =0;
	while (envs)
	{
		ft_putendl_fd(envs->key,2);
		envs = envs->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_env	envs;
	int i =0;
	envs.first = NULL;
	//env_print(env);
	while (env[i])
	{
		add_env(&envs, env[i]);
		i++;
	}
	//env_print(env);
	//printf("check : %s = %s\n",envs.next->value,envs.next->key);
	//print_envs(&envs);
	init_shlvl(&envs);
	prompt(&envs,env);
	return (0);
}
