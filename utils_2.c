/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:16:31 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/08/17 13:18:26 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_death_status(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->program->death_status);
	philo->program->someone_died = 1;
	pthread_mutex_unlock(&philo->program->death_status);
}

long	get_meal_time(t_philosopher *philo)
{
	long	last_meal_time;

	pthread_mutex_lock(&philo->meal_mutex);
	last_meal_time = philo->last_meal;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (last_meal_time);
}

void	set_meal_time(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->number_of_meals++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_mutex);
}

int	get_death_status(t_program *prog)
{
	int	status;

	pthread_mutex_lock(&prog->death_status);
	status = prog->someone_died;
	pthread_mutex_unlock(&prog->death_status);
	return (status);
}

void	print_status(t_philosopher *philo, char *status)
{
	long long	current_time;

	if (!ft_strncmp(status, "died", 4))
	{
		pthread_mutex_lock(&philo->program->print);
		current_time = get_time() - philo->program->start_time;
		printf("%lld %d %s\n", current_time, philo->id + 1, status);
		pthread_mutex_unlock(&philo->program->print);
		return ;
	}
	if (get_death_status(philo->program))
		return ;
	pthread_mutex_lock(&philo->program->print);
	if (!get_death_status(philo->program))
	{
		current_time = get_time() - philo->program->start_time;
		printf("%lld %d %s\n", current_time, philo->id + 1, status);
	}
	pthread_mutex_unlock(&philo->program->print);
}
