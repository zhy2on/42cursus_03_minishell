/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:41:26 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/03 19:20:08 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**create_args(t_token *tokens)
{
	int		i;
	char	**ret;
	t_token	*ptr;

	i = 0;
	ptr = tokens->first;
	while (ptr)
	{
		i++;
		ptr = ptr->next;
	}
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	ptr = tokens->first;
	while (ptr)
	{
		ret[i++] = ptr->str;
		ptr = ptr->next;
	}
	ret[i] = NULL;
	return (ret);
}

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
		str = readline("minishell$ ");
		tokens = (t_token *)malloc(sizeof(t_token));
		tokens->first = NULL;
		add_history(str);
		if (parsing_cmd(str, tokens) == ERROR)
			continue ;
		args = create_args(tokens);
		printf("token first: %p\n", tokens->first);
		if (builtin(envs, args) == SUCCESS)
			continue ;
		else
			exec(args, env, envs);
		free_token(tokens);
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
