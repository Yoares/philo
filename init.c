/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:01:46 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/07/14 13:15:38 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_data *data)
{
    int i;

    data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
    if (!data->forks)
        return (0);
    i = 0;
    while(i < data->nb_philo)
    {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0)
            return (0);
        i++;
    }
    if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (0);
	return (1);
}

int	init_philosophers(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (0);
	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		i++;
	}
	return (1);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].last_meal = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL, 
			philo_routine, &data->philos[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_lock);
	
	free(data->forks);
	free(data->philos);
}
