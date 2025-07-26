/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:01:37 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/07/26 20:06:38 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_lock);
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->meal_lock);
	return (0);
}

int	eat(t_philo *philo)
{
	pthread_mutex_t *first_fork;
	pthread_mutex_t *second_fork;
	
	if (check_death_status(philo))
		return (1);
	if (philo->left_fork < philo->right_fork)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_lock(first_fork);
	print_action(philo, "has taken a fork");
	
	if (check_death_status(philo))
	{
		pthread_mutex_unlock(first_fork);
		return (1);
	}
	
	pthread_mutex_lock(second_fork);
	print_action(philo, "has taken a fork");
	
	if (check_death_status(philo))
	{
		pthread_mutex_unlock(second_fork);
		pthread_mutex_unlock(first_fork);
		return (1);
	}
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_lock);
	
	print_action(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philo == 1)
	{
		print_action(philo, "has taken a fork");
		ft_usleep(philo->data->time_to_die);
		print_action(philo, "died");
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2);
	while (!check_death_status(philo))
	{
		print_action(philo, "is thinking");
		
		if (eat(philo))
			break;
		pthread_mutex_lock(&philo->data->meal_lock);
		if (philo->data->must_eat != -1 && 
			philo->meals_eaten >= philo->data->must_eat)
		{
			pthread_mutex_unlock(&philo->data->meal_lock);
			break;
		}
		pthread_mutex_unlock(&philo->data->meal_lock);
		print_action(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
	}
	return (NULL);
}
