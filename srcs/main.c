/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:41:26 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/10 16:06:55 by jihoh            ###   ########.fr       */
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
<<<<<<< HEAD
void	print_lst(t_token *lst)
{
	while (lst != NULL)
	{
		ft_putendl_fd(lst->str,2);
		lst = lst->next;
	}
}
void	prompt(t_env *envs,char **env)
=======

void	prompt(t_lsts *lsts, char **env)
>>>>>>> origin/jihoh
{
	char	*str;
	char	**args;

	//set_signal();
	while (1)
	{	
		int k = 0;
		set_signal();
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
<<<<<<< HEAD
		{
			print_lst(&tokens);
			// while(args[k])
				// fprintf(stderr,"check args : %s\n",args[k++]);
			pre_exec(args, envs,&tokens);
		}
		free_token(&tokens);
=======
			exec(args, env, &lsts->envs);
		free_token(&lsts->tokens);
>>>>>>> origin/jihoh
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
