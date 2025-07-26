/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:01:46 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/07/26 19:03:23 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_print_lock(t_data *data)
{
	int i;

	i = 0;
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
	{
		while (i > 0)
		{
			i--;
			pthread_mutex_destroy(&data->forks[i]);
		}
		free(data->forks);
		return (1);
	}
	return (0);
}

int	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (0);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(&data->forks[i]);
			}
			free(data->forks);
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init(&data->meal_lock, NULL) != 0)
		return (error_msg("Failed to init meal_lock"));
	if (init_print_lock(data))
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
		data->philos[i].last_meal = data->start_time;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];	// fork assigne 
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		i++;
	}
	return (1);
}

int	create_threads(t_data *data)
{
	int	i, j;

	i = 0;
	while(i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, 
			philo_routine, 
			&data->philos[i]) != 0)
		{
			pthread_mutex_lock(&data->meal_lock);
			data->someone_died = 1;
			pthread_mutex_unlock(&data->meal_lock);
			j = 0;
			while (j < i)
			{
				pthread_join(data->philos[j].thread, NULL);
				j++;
			}
			return (0);
		}
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
	while(i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->meal_lock);
	free(data->philos);
	free(data->forks);
}
