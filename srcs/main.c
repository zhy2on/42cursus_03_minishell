/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:41:26 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/06 19:42:44 by jihoh            ###   ########.fr       */
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
	parsing_line(str, &quot, i, lsts);
	tmp = lsts->tokens.first;
	while (tmp)
	{
		printf("%d %s\n", tmp->type, tmp->str);
		tmp = tmp->next;
	}
	if (quot)
	{
		fprintf(stderr, "minishell: single quotate error\n");
		return (ERROR);
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
		args = create_args(&tokens);
		if (builtin(envs, args) == SUCCESS)
			continue ;
		else
			exec(args, env, envs);
		free_token(&tokens);
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
