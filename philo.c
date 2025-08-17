/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:01:37 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/08/17 16:24:27 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
/ Special circular arrangement for first 3 philosophers
*/
static void init_group_of_three(t_program *program)
{
	program->philosophers[0].left_fork = &program->forks[0];
	program->philosophers[0].right_fork = &program->forks[1];
	program->philosophers[1].left_fork = &program->forks[1];
	program->philosophers[1].right_fork = &program->forks[2];
	program->philosophers[2].left_fork = &program->forks[2];
	program->philosophers[2].right_fork = &program->forks[0];
}

static void init_group_of_two(t_program *program, int start)
{
	int	i;
	int	philo_idx;
	int	other_idx;

	i = 0;
	while (i < 2 && (start + i) < program->nb_of_philosophers)
	{
		philo_idx = start + i;
		other_idx = (start + ((i + 1) % 2));
		program->philosophers[philo_idx].left_fork = &program->forks[philo_idx];
		program->philosophers[philo_idx].right_fork = &program->forks[other_idx];
		i++;
	}
}

static void	init_basic_data(t_program *program)
{
	int	i;
	int	num_philo;

	i = 0;
	program->current_turn = 0;
	num_philo = program->nb_of_philosophers;
	while (i < num_philo)
	{
		program->philosophers[i].id = i;
		program->philosophers[i].program = program;
		program->philosophers[i].number_of_meals = 0;
		i++;
	}
}

static void	init_groups(t_program *program)
{
	int	num_philo;
	int	i;

	num_philo = program->nb_of_philosophers;
	if (num_philo % 2 != 0)
	{
		init_group_of_three(program);
		i = 3;
		while (i < num_philo)
		{
			init_group_of_two(program, i);
			i += 2;
		}
		
	}
	else
	{
		i = 0;
		while (i < num_philo)
		{
			init_group_of_two(program, i);
			i += 2;
		}
	}
}

void	init_philosophers(t_program *program)
{
	init_basic_data(program);
	init_groups(program);
}
