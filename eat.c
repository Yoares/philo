/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:05:05 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/08/17 13:18:28 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philosopher *philo, pthread_mutex_t **first_fork,
		pthread_mutex_t **second_fork)
{
	if (philo->id % 2 == 0)
	{
		*first_fork = philo->right_fork;
		*second_fork = philo->left_fork;
	}
	else
	{
		*first_fork = philo->left_fork;
		*second_fork = philo->right_fork;
	}
	pthread_mutex_lock(*first_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(*second_fork);
	print_status(philo, "has taken a fork");
}

int	eat(t_philosopher *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (get_death_status(philo->program))
		return (1);
	take_forks(philo, &first_fork, &second_fork);
	if (get_death_status(philo->program))
	{
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
		return (1);
	}
	print_status(philo, "is eating");
	set_meal_time(philo);
	ft_usleep(philo->program->time_to_eat, philo->program);
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
	return (0);
}

int	sleep_think_actions(t_philosopher *philo)
{
	if (get_death_status(philo->program))
		return (1);
	print_status(philo, "is sleeping");
	ft_usleep(philo->program->time_to_sleep, philo->program);
	if (get_death_status(philo->program))
		return (1);
	print_status(philo, "is thinking");
	return (0);
}
