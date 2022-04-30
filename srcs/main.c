/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:41:26 by jihoh             #+#    #+#             */
/*   Updated: 2022/04/30 17:45:18 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		printf("minishell: single quotate error\n");
		return (ERROR);
	}
	return (SUCCESS);
}

void	prompt(t_env *envs)
{
	char	*str;
	char	**args;
	int		i;

	while (1)
	{
		args = malloc(sizeof(char *) * ARG_MAX);
		str = readline("🐚minishell$ ");
		add_history(str);
		if (parsing_cmd(str, args) == ERROR)
			continue ;
		if (builtin(envs, args) == SUCCESS)
			continue ;
		else
			exec(args);
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
