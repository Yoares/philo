/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:01:43 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/07/27 16:08:36 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_valid_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac != 5 && ac != 6)
		return (0);
	i = 1;
	while (i < ac)
	{
		j = 0;
		if (av[i][j] == '+')
			j++;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	parse_args(t_data *data, int ac, char **av)
{
	if (!is_valid_args(ac, av))
		return (0);
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->someone_died = 0;
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
	else
		data->must_eat = -1;
	if (data->nb_philo <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0
		|| (ac == 6 && data->must_eat <= 0))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!parse_args(&data, ac, av))
		return (error_msg("invalid arguments"));
	data.start_time = get_time();
	if (!init_mutexes(&data))
		return (error_msg("Failed to init mutexes"));
	if (!init_philosophers(&data))
		return (error_msg("Failed to init philosophers"));
	if (!create_threads(&data))
		return (error_msg("Failed to create threads"));
	monitor(&data);
	cleanup(&data);
	return (0);
}
