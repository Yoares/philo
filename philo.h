/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:55:03 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/07/26 18:31:22 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_data t_data;

typedef struct s_philo
{
	int             id;
	int             meals_eaten;
	long long       last_meal;
	pthread_t       thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	t_data          *data;
}	t_philo;

struct s_data
{
	int             nb_philo;
	int             time_to_die;
	int             time_to_eat;
	int             time_to_sleep;
	int             must_eat;
	long long       start_time;
	int             someone_died;

	pthread_mutex_t *forks;
	pthread_mutex_t print_lock;
	pthread_mutex_t meal_lock;
	t_philo         *philos;
};

// main.c
int		parse_args(t_data *data, int argc, char **argv);

// init.c
int		init_mutexes(t_data *data);
int		init_philosophers(t_data *data);
int		create_threads(t_data *data);
void	cleanup(t_data *data);

// utils.c
long long	get_time(void);
void		ft_usleep(long long time);
long		ft_atoi(const char *str);
int			ft_isdigit(int n);
int			error_msg(char *msg);
void		print_action(t_philo *philo, char *action);

// philo.c
void		*philo_routine(void *arg);

// monitor.c
void		monitor(t_data *data);
int			check_death(t_data *data);
int			check_meals_completed(t_data *data);

#endif
