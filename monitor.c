/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:01:40 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/07/27 15:00:07 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_data *data)
{
	long long	current_t;
	long long	last_meal;
	int			i;

	i = 0;
	current_t = get_time();
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->meal_lock);
		last_meal = data->philos[i].last_meal;
		pthread_mutex_unlock(&data->meal_lock);
		if ((current_t - last_meal) > data->time_to_die)
		{
			pthread_mutex_lock(&data->meal_lock);
			data->someone_died = 1;
			pthread_mutex_unlock(&data->meal_lock);
			pthread_mutex_lock(&data->print_lock);
			printf("%lld %d died\n", current_t - data->start_time,
				data->philos[i].id);
			pthread_mutex_unlock(&data->print_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_meals_completed(t_data *data)
{
	int	i;
	int	completed_meals;

	if (data->must_eat == -1)
		return (0);
	completed_meals = 0;
	pthread_mutex_lock(&data->meal_lock);
	i = 0;
	while (i < data->nb_philo)
	{
		if (data->philos[i].meals_eaten >= data->must_eat)
			completed_meals++;
		i++;
	}
	if (completed_meals == data->nb_philo)
	{
		data->someone_died = 1;
		pthread_mutex_unlock(&data->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->meal_lock);
	return (0);
}

void	monitor(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->meal_lock);
		if (data->someone_died)
		{
			pthread_mutex_unlock(&data->meal_lock);
			break ;
		}
		pthread_mutex_unlock(&data->meal_lock);
		if (check_death(data) || check_meals_completed(data))
			break ;
		usleep(100);
	}
}
