/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:25:22 by jihoh             #+#    #+#             */
/*   Updated: 2022/05/10 14:38:19 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset(t_env *envs, char **args)
{
	char	*s;
	t_env	*ptr;

	args = args + 1;
	while (*args)
	{
		s = *args;
		while (*s)
		{
			if (!ft_isalnum(*s))
			{
				printf("minishell: unset: `%s': not a valid identifier\n",
					*args);
				break ;
			}
			s++;
		}
		if (!*s)
			remove_env(envs, *args);
		args++;
	}
}
/*
*** export 만 여기서 정렬 헤서 출력만 그렇게 하게 
*/
t_env	*sort_env_list(t_env *temp)
{
	t_env *ptr;
	t_env *ptr2;
	char *temp_key;
	char *temp_value;
	int key;

	t_env *check;
	check = temp->first;
	
	ptr = temp->first;
	// ptr2 = ptr->next;
	// fprintf(stderr,"%s=%s\n",ptr->key,ptr->value);
	while (ptr)
	{
		ptr2 = ptr->next;
		while (ptr2)
		{
			// fprintf(stderr,"TEST : %d\n",ft_strcmp(ptr->key,ptr2->key));
			if (ft_strcmp(ptr->key,ptr2->key) > 0)
			{
				temp_key = ptr->key;
				ptr->key = ptr2->key;
				ptr2->key = temp_key;
				temp_value = ptr->value;
				ptr->value = ptr2->value;
				ptr2->value = temp_value;
			}
			// fprintf(stderr,"DAN : %c\t %c\t : %d\n",ptr->key[0],ptr2->key[0],ptr->key[0]-ptr2->key[0]);
			ptr2= ptr2->next;	
		}
		ptr = ptr->next;
	}
	// while (check)
	// {
	// 	fprintf(stderr,"%s=%s\n",check->key,check->value);
	// 	check =check->next;
	// }
	return (temp);
}

// t_env	*new_copy_env_list(t_env *envs)
// {
// 	t_env	*ret;

// 	envs = envs->first;
// 	ret->fir
// 	while (envs)
// 	{
// 		ret = get_env_node(ft_strdup(envs->key), ft_strdup(envs->value));
// 		envs = envs->next;
// 	}
// 	return (ret);
// }

t_env	*copy_env_list(t_env *envs)
{
	t_env *ptr;
	t_env *ptr2;
	t_env *temp;
	char *joinstr;
	temp = envs->first;
	temp->first = NULL;
	
	t_env *check;

	ptr = (envs)->first;
	// temp = temp->first;
	// temp->first = get_env_node(ptr->key,ptr->value);
	while(ptr)
	{
		// if(!ptr->value)
		// 	break;
		// fprintf(stderr,"TEST : %s \t %s\n",(ptr->key),(ptr->value));
		if (ptr->key && ptr->value)
		{
			joinstr = NULL;
			joinstr = ft_strjoin(ptr->key,"=");
			joinstr = ft_strjoin(joinstr,ptr->value);
			// fprintf(stderr,"join TEST: %s\n",joinstr);
			add_env(temp,joinstr);
		}
		ptr = ptr->next;
			// fprintf(stderr,"temp TEST: %s=%s\n",temp->first->key,temp->first->value);
		// break ;
		// temp->first = get_env_node(ptr->key,ptr->value);
		// fprintf(stderr,"Temp TEst : %s=%s\n",temp->first->key,temp->first->value);
		// break;
	}
	// check = sort_env_list(temp);
	// fprintf(stderr,"-----------------------\n");
	// while (check)
	// {
	// 	fprintf(stderr,"TEST : %s=%s\n",check->key,check->value);
	// 	check = check->next;
	// }
	return (sort_env_list(temp));
}
////

void	export(t_env *envs, char **args)
{
	t_env	*ptr;

	//ptr = copy_env_list(envs);
	// ptr = NULL;
	// ptr = envs->first;
	if (!args[1])
	{
		ptr = copy_env_list(envs)->first;
		// ptr = envs->first;
		while (ptr)
		{
			printf("declare -x %s", ptr->key);
			if (ptr->value)
				printf("=\"%s\"", ptr->value);
			printf("\n");
			ptr = ptr->next;
		}
	}
	else
	{
		args = args + 1;
		while (*args)
		{
			add_env(envs, *args);
			args++;
		}
	}
}

void	echo(char **args)
{
	char	*ptr;

	if (!args[1] && printf("\n"))
		return ;
	ptr = args[1];
	if (*ptr == '-')
	{
		while (*(++ptr) == 'n')
			;
		if (*ptr == '\0')
		{
			args += 2;
			while (*args && *(args + 1))
				printf("%s ", *args++);
			if (*args)
				printf("%s", *args);
			return ;
		}
	}
	args += 1;
	while (*args && *(args + 1))
		printf("%s ", *args++);
	if (*args)
		printf("%s\n", *args);
}

int	builtin(t_env *envs, char **args)
{
	char	cwd[PATH_MAX];
	char	*ptr;

	if (!args[0])
		return (SUCCESS);
	if (!ft_strcmp(args[0], "pwd"))
		printf("%s\n", getcwd(cwd, PATH_MAX));
	else if (!ft_strcmp(args[0], "cd"))
		cd(envs, args);
	else if (!ft_strcmp(args[0], "echo"))
		echo(args);
	else if (!ft_strcmp(args[0], "env"))
		env(envs);
	else if (!ft_strcmp(args[0], "export"))
		export(envs, args);
	else if (!ft_strcmp(args[0], "unset"))
		unset(envs, args);
	else
		return (ERROR);
	return (SUCCESS);
}
