/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:01:37 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/07/25 17:36:19 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*1. Start thinking
   Print: "100 2 is thinking"

2. Acquire forks (order: fork1, then fork2)
   Lock fork1 → Print: "105 2 has taken a fork"  
   Lock fork2 → Print: "106 2 has taken a fork"

3. Start eating
   Print: "107 2 is eating"
   last_meal = 107
   meals_eaten = 1
   Sleep for time_to_eat

4. Release forks
   Unlock fork2
   Unlock fork1

5. Start sleeping  
   Print: "207 2 is sleeping"
   Sleep for time_to_sleep

6. Check conditions
   - someone_died? No
   - enough meals? No
   → Continue loop (back to thinking)*/

void	*philo_routine(void *arg)
{
	t_philo  *philo;

   philo = (t_philo *)arg;
}
