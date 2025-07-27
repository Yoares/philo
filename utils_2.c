/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:16:31 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/07/27 15:17:04 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long long time)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(500);
}

int	error_msg(char *msg)
{
	printf("Error: %s\n", msg);
	return (0);
}

void	print_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->data->meal_lock);
	if (!philo->data->someone_died)
	{
		pthread_mutex_lock(&philo->data->print_lock);
		printf("%lld %d %s\n", get_time() - philo->data->start_time,
			philo->id, action);
		pthread_mutex_unlock(&philo->data->print_lock);
	}
	pthread_mutex_unlock(&philo->data->meal_lock);
}
