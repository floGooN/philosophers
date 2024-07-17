/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 08:54:31 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/17 08:57:25 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/*
  * take an instance of philo_tab and a code action as parameter
  * print the message associate with the right ation
  * action 0 -> take a fork
  * action 1 -> eating
  * action 2 -> sleeping
  * action 3 -> thinking
  * action 4 -> died
*/
bool  print_message(t_philo *philo, int action)
{
    long int  curr_time;
    long int  time1;
    long int  time2;

    time1 = get_time();

    if (pthread_mutex_lock(philo->shared_mtx.print_mtx))
      return (print_error("error -> failure to take print_mutex\n"), 1);
    if (check_death(philo))
      return (pthread_mutex_unlock(philo->shared_mtx.print_mtx), 1);

    curr_time = time1 - philo->time_data.start_time;
    time2 = get_time();
    philo->time_data.time_to_die -= time2 - time1;

    if (philo->time_data.time_to_die <= 0)
      action = 4;
    // PRINT FUNCTION
    if (action == 0)
      printf("%ld %d has taken a fork\n", curr_time, philo->index);
    else if (action == 1)
      printf("%ld %d is eating\n", curr_time, philo->index);
    else if (action == 2)
      printf("%ld %d is sleeping\n", curr_time, philo->index);
    else if (action == 3)
      printf("%ld %d is thinking\n", curr_time, philo->index);
    else if (action > 3)
    {
      change_death_status(philo);
      printf("%ld %d died\n", curr_time, philo->index);
      return (pthread_mutex_unlock(philo->shared_mtx.print_mtx), 1);
    }
    // PRINT FUNCTION

    if (pthread_mutex_unlock(philo->shared_mtx.print_mtx))
      return (print_error("error -> failure to drop print_mutex\n"), 1);
    return (0);
}
