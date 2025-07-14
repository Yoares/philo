/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:01:37 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/07/14 13:15:38 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	
	pthread_mutex_lock(&philo->data->print_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->print_lock);
	
	print_action(philo, "is eating");
	philo->meals_eaten++;
	ft_usleep(philo->data->time_to_eat);
	
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2);
	
	while (!philo->data->someone_died)
	{
		eat(philo);
		
		if (philo->data->must_eat != -1 && 
			philo->meals_eaten >= philo->data->must_eat)
			break;
		
		print_action(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		
		print_action(philo, "is thinking");
	}
	return (NULL);
}

