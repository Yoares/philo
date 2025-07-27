/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:05:05 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/07/27 15:05:37 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_forks(t_philo *philo,
	pthread_mutex_t **first, pthread_mutex_t **second)
{
	if (philo->left_fork < philo->right_fork)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
}

static int	try_take_forks(t_philo *philo,
	pthread_mutex_t *first, pthread_mutex_t *second)
{
	pthread_mutex_lock(first);
	print_action(philo, "has taken a fork");
	if (check_death_status(philo))
	{
		pthread_mutex_unlock(first);
		return (1);
	}
	pthread_mutex_lock(second);
	print_action(philo, "has taken a fork");
	if (check_death_status(philo))
	{
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(first);
		return (1);
	}
	return (0);
}

static void	update_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_lock);
}

int	eat(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (check_death_status(philo))
		return (1);
	lock_forks(philo, &first, &second);
	if (try_take_forks(philo, first, second))
		return (1);
	update_meal(philo);
	print_action(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
	return (0);
}
