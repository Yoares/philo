/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:55:03 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/08/16 23:49:26 by ykhoussi         ###   ########.fr       */
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

typedef struct s_data	t_data;

typedef struct s_philosopher {
    int id;                      // Philosopher identifier (0-based)
    int number_of_meals;         // Meals eaten counter
    long long last_meal;         // Timestamp of last meal
    pthread_mutex_t *left_fork;  // Pointer to left fork mutex
    pthread_mutex_t *right_fork; // Pointer to right fork mutex
    pthread_mutex_t meal_mutex;  // Protects meal-related data
    struct s_program *program;   // Back-reference to main program
} t_philosopher;

typedef struct s_program {
    // Program parameters
    int nb_of_philosophers;
    int time_to_die, time_to_eat, time_to_sleep;
    int must_eat_count;          // Optional: minimum meals required
    
    // Timing and status
    long long start_time;
    int someone_died;
    
    // Synchronization primitives
    pthread_mutex_t death_status; // Protects death flag
    pthread_mutex_t print;        // Serializes output
    pthread_mutex_t *forks;       // Array of fork mutexes
    pthread_mutex_t turn_mutex;   // For odd-numbered cases
    int current_turn;             // Turn-based system for 3 philosophers
    
    // Thread management
    pthread_t *threads;           // Philosopher threads
    pthread_t *monitor;           // Death monitor thread
    t_philosopher *philosophers;  // Philosopher data
} t_program;

/* time functions */
long long					get_time(void);
void					ft_usleep(long time_in_ms, t_program *prog);
int						critical_timing(t_program *prog);

/* utility functions */
void					print_status(t_philosopher *philo, char *status);
int						get_death_status(t_program *prog);
void					set_death_status(t_philosopher *philo);
long					get_meal_time(t_philosopher *philo);
void					set_meal_time(t_philosopher *philo);
int						ft_strncmp(const char *s1, const char *s2, size_t n);

/* initialization functions */
int						check_args(int ac, char **av);
int						init_program_args(t_program *program, int ac,
							char **av);
void					*monitor_routine(void *arg);
int						init_program(t_program *program);
int						init_mutexes(t_program *program);
void					init_philosophers(t_program *program);

/* philosopher actions */
void					take_forks_3(t_philosopher *philo);
int						eat(t_philosopher *philo);
int						eat_3(t_philosopher *philo);
int						sleep_think_actions(t_philosopher *philo);
void					*philosopher_routine(void *arg);
void					*philosopher_routine_3(void *arg);

/* cleanup functions */
void					clean_program(t_program *program);

#endif
