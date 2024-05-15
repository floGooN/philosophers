/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:21:00 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/15 17:47:20 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "stdio.h"
#include <unistd.h>
#include <sys/time.h>

#include "action.h"

bool  eat_act(t_philo *philo);
bool  sleep_act(t_philo *philo);
bool  think_act(void *arg);
long int  get_time(void);

static void wait_loop(t_philo *philo)
{
  while (1)
  {
    pthread_mutex_lock(philo->ready_mutex);
    if (READY_PTR)
    {
      pthread_mutex_unlock(philo->ready_mutex);
      break;
    }
    pthread_mutex_unlock(philo->ready_mutex);
  }
}

void  *odd_routine(void *arg)
{
  t_philo *philo;

  philo = (t_philo *) arg;
  wait_loop(philo);
  philo->start_time = get_time();
  while (!ISDEAD_PTR)
  {
    if (ISDEAD_PTR || eat_act(philo))
      break;
    if (ISDEAD_PTR || sleep_act(philo))
      break;
    // if (!ISDEAD_PTR)
    // {
    //   if (think_act(philo))
    //     return (NULL);
    // }
    // if (philo->nb_meal == 0)
    //   break ;
  }
  printf("EXIT ODD ROUTINE\n");
  return (NULL);
}

void  *even_routine(void *arg)
{
  t_philo *philo;

  philo = (t_philo *) arg;
  wait_loop(philo);
  philo->start_time = get_time();
  while (!ISDEAD_PTR)
  {
    if (ISDEAD_PTR || sleep_act(philo))
      break;
    // if (philo->time_to_die > 0 && !ISDEAD_PTR)
    // {
    //   if (think_act(philo))
    //     break;
    // }
    // if (philo->nb_meal == 0)
    //   break ;
    if (ISDEAD_PTR || eat_act(philo))
        break;
  }
  printf("EXIT EVEN ROUTINE\n");
  return (NULL);
}
