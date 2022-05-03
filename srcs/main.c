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
		printf("minishell: single quotate error\n");
		return (ERROR);
	}
	return (SUCCESS);
}

void	prompt(t_env *envs)
{
	char	*str;
	char	**args;
	t_token	*tokens;
	int		i;

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

int	main(int ac, char **av, char **env)
{
	t_env	envs;

	envs.first = NULL;
	while (*env)
	{
		add_env(&envs, *env);
		env++;
	}
	prompt(&envs);
	return (0);
}
