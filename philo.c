/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:01:37 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/07/25 19:51:52 by ykhoussi         ###   ########.fr       */
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
   pthread_mutex_t (*first_fork), (*second_fork);

   philo = (t_philo *)arg;
   if (philo->data->nb_philo == 1)  //handel single philo
   {
      print_action(philo, "has taken a fork");
      //it should bee sleep
      return (NULL);
   }
   while (!philo->data->someone_died) // life cycle
   {
      print_action(philo, " is thinking");
      if (philo->left_fork < philo->right_fork) // to avoid deadlock
      {
         first_fork = philo->left_fork;
         second_fork = philo->right_fork;
      }
      else
      {
         first_fork = philo->right_fork;
         second_fork = philo->left_fork;
      }
      pthread_mutex_lock(first_fork);
      print_action(philo, "has taken a fork");
      pthread_mutex_lock(second_fork);
      print_action(philo, "has taken a fork");

      //eathing
      print_action(philo, "is eating");
      philo->last_meal = getime();

   }
}
