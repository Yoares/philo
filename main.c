/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:01:43 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/08/16 23:49:08 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	handle_one_philo(t_program *prog)
{
	long long start_time;

	prog->start_time = get_time();
	start_time = get_time() - prog->start_time;
	printf("%lld %d %s\n", start_time, 1, "has taken a fork");
	ft_usleep(prog->time_to_die, prog);
	start_time = get_time() - prog->start_time;
	printf("%lld %d %s\n", start_time, 1, "is dead");
	return (0);
}

int	main(int ac, char **av)
{
	t_program	program;

	if (check_args(ac, av))
		return (EXIT_FAILURE);
	if (init_program_args(&program, ac, av))
		return (EXIT_FAILURE);
	if (program.nb_of_philosophers == 1)
		return (handle_one_philo(&program));
	if (init_program(&program))
		return (EXIT_FAILURE);
	clean_program(&program);
	return (0);
}
