/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:41:26 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/24 11:23:17 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parsing_cmd(char *str, t_mini *mini)
{
	int		i;
	char	quot;
	t_token	*tmp;

	i = 0;
	quot = '\0';
	if (!parsing_line(str, mini))
		return (0);
	tmp = mini->tokens;
	while (tmp)
	{
		printf("%d %s\n", tmp->type, tmp->str);
		tmp = tmp->next;
	}
	return (1);
}

void	prompt(t_mini *mini)
{
	char	*str;

	while (1)
	{
		init_inout(mini);
		init_fd(mini);
		set_signal();
		str = readline("🐚minishell$ ");
		if (str && *str)
			add_history(str);
		if (parsing_cmd(str, mini) && syntax_check(mini, mini->tokens))
			run_cmd_line(mini, mini->tokens, NULL);
		free_token(&mini->tokens);
		free(str);
	}
}

int	main(int ac, char **av, char **env)
{
	t_mini	mini;
	t_env	*ptr;

	ac = 0;
	av[1] = NULL;
	init_mini(&mini);
	while (*env)
		add_env(&mini.envs, ft_strdup(*env++));
	ptr = mini.envs;
	init_shlvl(&mini.envs);
	prompt(&mini);
	return (0);
}
