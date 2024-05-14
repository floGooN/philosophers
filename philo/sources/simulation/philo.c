/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:21:00 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/14 12:24:44 by fberthou         ###   ########.fr       */
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

static void wait_loop(t_philo *philo)
{
  while (!READY_PTR)
    ;
}

void  *odd_routine(void *arg)
{
  t_philo *philo;

  philo = (t_philo *) arg;
  wait_loop(philo);
  gettimeofday(&philo->philo_tv, NULL);
  while (!ISDEAD_PTR)
  {
    if (ISDEAD_PTR || eat_act(philo))
      return (NULL);
    if (ISDEAD_PTR || sleep_act(philo))
      return (NULL);
    // if (!ISDEAD_PTR)
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
  while (!ISDEAD_PTR)
  {
    if (ISDEAD_PTR || sleep_act(philo))
      return (NULL);
    // if (philo->time_to_die > 0 && !ISDEAD_PTR)
    // {
    //   if (think_act(philo))
    //     return (NULL);
    // }
    // if (philo->nb_meal == 0)
    //   break ;
    if (ISDEAD_PTR || eat_act(philo))
      return (NULL);
  }
  return (NULL);
}
