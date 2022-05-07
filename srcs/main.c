/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:41:26 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/07 18:33:05 by jihoh            ###   ########.fr       */
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

int	parsing_cmd(char *str, t_lsts *lsts)
{
	int		i;
	char	quot;
	t_token	*tmp;

	i = 0;
	quot = '\0';
	if (parsing_line(str, lsts) == ERROR)
		return (ERROR);
	tmp = lsts->tokens.first;
	while (tmp)
	{
		printf("%d %s\n", tmp->type, tmp->str);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

void	prompt(t_lsts *lsts, char **env)
{
	char	*str;
	char	**args;

	//set_signal();
	while (1)
	{
		str = readline("🐚minishell$ ");
		eof_history(str);
		if (!*str)
			continue ;
		lsts->tokens.first = NULL;
		if (parsing_cmd(str, lsts) == ERROR)
			continue ;
		/*
		args = create_args(&lsts->tokens);
		if (builtin(&lsts->envs, args) == SUCCESS)
			continue ;
		else
			exec(args, env, &lsts->envs);
		free_token(&lsts->tokens);
		free(args);
		*/
		free(str);
	}
}

int	main(int ac, char **av, char **env)
{
	t_lsts	lsts;
	int		i;

	i = 0;
	lsts.envs.first = NULL;
	while (env[i])
		add_env(&lsts.envs, env[i++]);
	init_shlvl(&lsts.envs);
	prompt(&lsts, env);
	return (0);
}
