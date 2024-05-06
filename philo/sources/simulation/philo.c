/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:21:00 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/06 12:19:06 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "stdio.h"
#include <unistd.h>
#include <sys/time.h>

bool  eat_act(t_philo *philo);
bool  sleep_act(t_philo *philo);
bool  think_act(void *arg);

static void wait_loop(t_philo *philo)
{
  while (1)
  {
    pthread_mutex_lock(philo->ready_mutex);
    if (*(philo->ready))
      break ;
    else
      pthread_mutex_unlock(philo->ready_mutex);
  }
  pthread_mutex_unlock(philo->ready_mutex);
}

void  *odd_routine(void *arg)
{
  t_philo *philo;

  philo = (t_philo *) arg;
  wait_loop(philo);
  // pthread_mutex_lock(philo->print_mutex);
  // printf("ODD : deadtime = %d\n", philo->time_to_die);
  // pthread_mutex_unlock(philo->print_mutex);
  gettimeofday(&philo->philo_tv, NULL);
  while (philo->time_to_die > 0 && !*(philo->is_dead))
  {
    if (eat_act(philo))
      return (NULL);
    if (philo->time_to_die > 0 && !*(philo->is_dead))
    {
      if (sleep_act(philo))
        return (NULL);
    }
    // if (philo->time_to_die > 0 && !*(philo->is_dead))
    // {
    //   if (think_act(philo))
    //     return (NULL);
    // }
    // if (philo->nb_meal == 0)
    //   break ;
  }
  return (NULL);
}

void  *even_routine(void *arg)
{
  t_philo *philo;

  philo = (t_philo *) arg;
  wait_loop(philo);
  gettimeofday(&philo->philo_tv, NULL);
    // pthread_mutex_lock(philo->print_mutex);
    // printf("EVEN : deadtime = %d\n", philo->time_to_die);
    // pthread_mutex_unlock(philo->print_mutex);
  while (philo->time_to_die > 0 && !*(philo->is_dead))
  {
    if (sleep_act(philo))
      return (NULL);
    // if (philo->time_to_die > 0 && !*(philo->is_dead))
    // {
    //   if (think_act(philo))
    //     return (NULL);
    // }
    // if (philo->nb_meal == 0)
    //   break ;
    if (philo->time_to_die > 0 && !*(philo->is_dead))
    {
      if (eat_act(philo))
        return (NULL);
    }
  }
  return (NULL);
}
