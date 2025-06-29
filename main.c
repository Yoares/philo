/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:01:43 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/06/29 18:50:08 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(t_data *data, int ac, char **av)
{
    int i = 1;
    if (ac != 5 && ac != 0)
        return (0);
    while (av[i] < ac)
    {
        if (!ft_isdigit(av[i]))
            return (0);
        i++;
    }
    data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
        data->must_eat = ft_atoi(av[5]);
    else
        data->must_eat = -1;
	data->someone_died = 0;
    
    if (data->nb_philo <= 0 || data->time_to_die <= 0 ||
	    data->time_to_eat <= 0 || data->time_to_sleep <= 0 ||
		(ac == 6 && data->must_eat <= 0))
		    return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!parse_args(&data, ac, av))
	{
        printf("Error: invalid arguments\n");
		return (1);
	}
}
