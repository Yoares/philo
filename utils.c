/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:01:32 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/08/11 20:29:48 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *str)
{
	int		i;
	int		s;
	size_t	r;

	s = 1;
	i = 0;
	r = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			s = -s;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - '0');
		i++;
	}
	if (r > LONG_MAX)
		return (0 - (s == 1));
	return (r * s);
}

static int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int ac, char **av)
{
	int	i;

	if (ac != 5 && ac != 6)
	{
		printf("Error: Wrong number of arguments\n");
		printf("Usage: ./philo number_of_philosophers time_to_die ");
		printf("time_to_eat time_to_sleep [number_of_times_must_eat]\n");
		return (1);
	}
	i = 0;
	while (++i < ac)
	{
		if (!is_number(av[i]))
		{
			printf("Error: Arguments must be positive numbers\n");
			return (1);
		}
	}
	return (0);
}

int	init_program_args(t_program *program, int ac, char **av)
{
	program->nb_of_philosophers = ft_atoi(av[1]);
	program->time_to_die = ft_atoi(av[2]);
	program->time_to_eat = ft_atoi(av[3]);
	program->time_to_sleep = ft_atoi(av[4]);
		program->must_eat_count = -1;
	if (ac == 6)
		program->must_eat_count = ft_atoi(av[5]);
	if (program->nb_of_philosophers <= 0 || program->time_to_die <= 0
		|| program->time_to_eat <= 0 || program->time_to_sleep <= 0
		|| (ac == 6 && program->must_eat_count <= 0))
	{
		printf("Error: Invalid arguments (must be positive numbers)\n");
		return (1);
	}
	if (program->nb_of_philosophers > 200)
	{
		printf("Error: Too many philosophers (maximum is 200)\n");
		return (1);
	}
	return (0);
}
