/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:01:40 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/07/14 13:15:39 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_data *data)
{
	int			i;
	long long	current_time;

	i = 0;
	current_time = get_time();
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->print_lock);
		if ((current_time - data->philos[i].last_meal) > data->time_to_die)
		{
			printf("%lld %d died\n", current_time - data->start_time, 
				data->philos[i].id);
			data->someone_died = 1;
			pthread_mutex_unlock(&data->print_lock);
			return (1);
		}
		pthread_mutex_unlock(&data->print_lock);
		i++;
	}
	return (0);
}

int	check_meals_completed(t_data *data)
{
	int	i;

	if (data->must_eat == -1)
		return (0);
	
	i = 0;
	while (i < data->nb_philo)
	{
		if (data->philos[i].meals_eaten < data->must_eat)
			return (0);
		i++;
	}
	data->someone_died = 1;
	return (1);
}

void	monitor(t_data *data)
{
	while (!data->someone_died)
	{
		if (check_death(data) || check_meals_completed(data))
			break;
		usleep(1000);
	}
}