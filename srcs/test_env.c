int	main(int ac, char **av, char **env)
{
	int		i;

	i = 0;
	while (*env)
	{
		printf("%d: %s\n", i, *env);
		i++;
		(env)++;
	}
	return (0);
}
