/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:21:00 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/17 08:53:15 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <struct.h>
#include <philo.h>

static void wait_loop(t_philo *philo)
{
  while (1)
  {
    pthread_mutex_lock(philo->shared_mtx.ready_mtx);
    if (*(philo->ready))
    {
      	pthread_mutex_unlock(philo->shared_mtx.ready_mtx);
      	return ;
    }
    pthread_mutex_unlock(philo->shared_mtx.ready_mtx);
  }
}

void  *odd_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *) arg;
    wait_loop(philo);
    philo->time_data.start_time = get_time();
    while (!check_death(philo))
    {
        if (think_act(philo))
          return (NULL);
        if (check_death(philo) || eat_act(philo))
          return (NULL);
        // if (philo->nb_meal == 0)
        //   return (NULL);
        if (check_death(philo) || sleep_act(philo))
          return (NULL);
    }
    return (NULL);
}

void  *even_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *) arg;
    wait_loop(philo);
    philo->time_data.start_time = get_time();
    while (!check_death(philo))
    {
      if (sleep_act(philo))
        return (NULL);
      if (check_death(philo) || think_act(philo))
        return (NULL);
      if (check_death(philo) || eat_act(philo))
        return (NULL);
      // if (philo->nb_meal == 0)
      //   return (NULL);
    }
    return (NULL);
}
