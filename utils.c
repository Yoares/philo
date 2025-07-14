/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:01:32 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/07/14 13:15:37 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *str)
{
	int		i;
	int		s;
	size_t	r;

	s = 1;
	i = 0;
	r = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			s = -s;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - '0');
		i++;
	}
	if (r > LONG_MAX)
		return (0 - (s == 1));
	return (r * s);
}

int	ft_isdigit(int n)
{
	if (n >= 48 && n <= 57)
	{
		return (1);
	}
	return (0);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

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
	pthread_mutex_lock(&philo->data->print_lock);
	if (!philo->data->someone_died)
	{
		printf("%lld %d %s\n", get_time() - philo->data->start_time, 
			philo->id, action);
	}
	pthread_mutex_unlock(&philo->data->print_lock);
}
