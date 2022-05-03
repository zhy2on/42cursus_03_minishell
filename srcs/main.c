/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:41:26 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/03 13:39:37 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	env_print(char **env)
{
	int i =0;
	while (env[i])
	{
		ft_putendl_fd(env[i++],2);
	}
}

void	parsing_cmd_sub(char *str, char **args, char *quot, int i)
{
	while (*str)
	{
		if (!*quot && ft_isquot(*str))
		{
			*quot = *str;
			i++;
		}
		else if (*str == *quot)
		{
			*quot = '\0';
			i++;
		}
		else if (i > 0)
			*(str - i) = *str;
		if (!*quot && *str == ' ')
		{
			*(str - i) = '\0';
			*args++ = str - i + 1;
		}
		str++;
	}
	*args = NULL;
	*(str - i) = '\0';
}

int	parsing_cmd(char *str, char **args)
{
	int		i;
	char	quot;

	i = 0;
	*args++ = str;
	quot = '\0';
	parsing_cmd_sub(str, args, &quot, i);
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
	int		i;

	// env_print(env);

	while (1)
	{
		set_signal();
		args = malloc(sizeof(char *) * ARG_MAX);
		str = readline("🐚minishell$ ");
		if (parsing_cmd(str, args) == ERROR)
			continue ;
		if (builtin(envs, args) == SUCCESS)
			continue ;
		else
			exec(args,env,envs);
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
	int k = 0;
	//env_print(env);
	//printf("check : %s = %s\n",envs.next->value,envs.next->key);
	//print_envs(&envs);
	prompt(&envs,env);
	return (0);
}
