/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:21:00 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/16 19:44:42 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "stdio.h"
#include <unistd.h>
#include <sys/time.h>

#include "action.h"

bool      eat_act(t_philo *philo);
bool      sleep_act(t_philo *philo);
bool      think_act(void *arg);
long int  get_time(void);
bool      check_death(t_philo *philo);

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
  while (1)
  {
    usleep(50);
    if (pthread_mutex_lock(philo->print_mutex))
      return (print_error ("error -> failure to take print_mutex\n"), NULL);
    printf("ODD philo %d\n", philo->index);
    if (pthread_mutex_unlock(philo->print_mutex))
      return (print_error ("error -> failure to drop print_mutex\n"), NULL);

    // if (check_death(philo) || think_act(philo))
    //   break;
    // if (check_death(philo) || eat_act(philo))
    //   break;
    // if (check_death(philo) || sleep_act(philo))
    //   break;
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
  philo->start_time = get_time();
  while (1)
  {
    usleep(77);
    if (pthread_mutex_lock(philo->print_mutex))
      return (print_error ("error -> failure to take print_mutex\n"), NULL);
    printf("EVEN philo %d\n", philo->index);
    if (pthread_mutex_unlock(philo->print_mutex))
      return (print_error ("error -> failure to drop print_mutex\n"), NULL);

    // if (check_death(philo) || sleep_act(philo))
    //   break;
    // if (check_death(philo) || think_act(philo))
    //   break;
    // // if (philo->nb_meal == 0)
    // //   break ;
    // if (check_death(philo) || eat_act(philo))
    //     break;
  }
  return (NULL);
}
