/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 08:54:31 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/17 11:10:05 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int ft_print(t_philo *philo, long int curr_time, int action)
{
    if (action == 0)
      return (printf("%ld %d has taken a fork\n", curr_time, philo->index));
    if (action == 1)
      return (printf("%ld %d is eating\n", curr_time, philo->index));
    if (action == 2)
      return (printf("%ld %d is sleeping\n", curr_time, philo->index));
    if (action == 3)
      return (printf("%ld %d is thinking\n", curr_time, philo->index));
    else
    {
      change_death_status(philo);
      printf("%ld %d died\n", curr_time, philo->index);
      return (pthread_mutex_unlock(philo->shared_mtx.print_mtx), -1);
    }
    return (0);
}

bool  print_message(t_philo *philo, int action)
{
    long int  curr_time;
    long int  time1;

    time1 = get_time();
    if (pthread_mutex_lock(philo->shared_mtx.print_mtx))
      return (ft_perror("error -> failure to take print_mutex\n"), 1);
    curr_time = time1 - philo->time_data.start_time;
    philo->time_data.time_to_die -= get_time() - time1;
    if (check_death(philo))
      return (pthread_mutex_unlock(philo->shared_mtx.print_mtx), 1);
    if (philo->time_data.time_to_die <= 0)
      action = 4;
    if (ft_print(philo, curr_time, action) == -1)
      return (1);
    if (pthread_mutex_unlock(philo->shared_mtx.print_mtx))
      return (ft_perror("error -> failure to drop print_mutex\n"), 1);
    return (0);
}
