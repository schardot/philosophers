#include "../philo.h"

int check_args(t_info *in, int argc, char **argv)
{
	int i;

	if (argc != 5 && argc != 6)
	{
		printf("Incorrect number of arguments\n");
		return (1);
	}
	i = 0;
	while (++i < argc)
	{
		if (!is_argv_digit(argv[i]))
		{
			printf("All arguments need to be positive numbers\n");
			return (1);
		}
	}
    if (init_info(in, argc, argv))
    {
		printf("Error initiliazing info struct\n");
		return (1);
	}
	return (0);
}

int is_argv_digit(char *argv)
{
	int i;

	i = 0;
	while (argv[i])
	{
		if (!(argv[i] >= '0' && argv[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int ft_atoi(const char *n)
{
	int r;
	int sign;

	sign = 1;
	r = 0;
	while (ft_isspace(*n))
		n++;
	if (*n == '-' || *n == '+')
	{
		if (*n == '-')
			sign = -1;
		n++;
	}
	while (*n != '\0' && (*n >= '0' && *n <= '9'))
	{
		r = (r * 10) + (*n - '0');
		n++;
	}
	r *= sign;
	return (r);
}

int ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' ||
			c == '\v');
}
