/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 20:29:26 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/08/16 23:48:22 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long time_in_ms, t_program *prog)
{
	long	start;
	long	sleep_interval;

	start = get_time();
	if (prog->nb_of_philosophers > 100)
		sleep_interval = 500;
	else if (prog->nb_of_philosophers > 50)
		sleep_interval = 100;
	else
		sleep_interval = 50;
	while ((get_time() - start) < time_in_ms)
	{
		usleep(sleep_interval);
	}
}

long long	get_time(void)
{
	struct	timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n)
		i++;
	if (n == i)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	critical_timing(t_program *prog)
{
	int	ct;

	if (prog->nb_of_philosophers % 2 == 0)
		ct = (prog->time_to_die <= prog->time_to_eat + prog->time_to_sleep);
	else
		ct = (prog->time_to_die / 3 <= prog->time_to_eat + prog->time_to_sleep);
	return (ct);
}
