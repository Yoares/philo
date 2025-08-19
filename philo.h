/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:55:03 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/08/19 17:49:52 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/*
** Forward declaration
*/
typedef struct s_program	t_program;

/*
** Philosopher structure
*/
typedef struct s_philosopher
{
	int						id;
	int						number_of_meals;
	long long				last_meal;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	pthread_mutex_t			meal_mutex;
	t_program				*program;
}							t_philosopher;

/*
** Global program structure
*/
typedef struct s_program
{
	int						nb_of_philosophers;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						must_eat_count;

	long long				start_time;
	int						someone_died;

	pthread_mutex_t			death_status;
	pthread_mutex_t			print;
	pthread_mutex_t			*forks;
	pthread_mutex_t			turn_mutex;
	int						current_turn;

	pthread_t				*threads;
	pthread_t				*monitor;
	t_philosopher			*philosophers;
}							t_program;

/*
** Time functions
*/
long long					get_time(void);
void						ft_usleep(long time_in_ms, t_program *prog);
int							critical_timing(t_program *prog);

/*
** Utility functions
*/
void						print_status(t_philosopher *philo, char *status);
int							get_death_status(t_program *prog);
void						set_death_status(t_philosopher *philo);
long						get_meal_time(t_philosopher *philo);
void						set_meal_time(t_philosopher *philo);
int							ft_strncmp(const char *s1, const char *s2,
								size_t n);

/*
** Initialization functions
*/
int							check_args(int ac, char **av);
int							init_program_args(t_program *program, int ac,
								char **av);
void						*monitor_routine(void *arg);
int							init_program(t_program *program);
int							init_mutexes(t_program *program);
void						init_philosophers(t_program *program);

/*
** Philosopher actions
*/
void						take_forks_3(t_philosopher *philo);
int							eat(t_philosopher *philo);
int							eat_3(t_philosopher *philo);
int							sleep_think_actions(t_philosopher *philo);
void						*philosopher_routine(void *arg);
void						*philosopher_routine_3(void *arg);

/*
** Cleanup functions
*/
void						clean_program(t_program *program);

#endif
