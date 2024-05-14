/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:59:16 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/14 11:56:39 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "stdio.h"
#include <unistd.h>
#include <sys/time.h>

#include "action.h"

bool  print_message(t_philo *philo, int state)
{
  long int       curr_time;
  struct timeval tv;

  gettimeofday(&tv, NULL);
  curr_time = ((tv.tv_usec - philo->philo_tv.tv_usec) + \
              (tv.tv_sec - philo->philo_tv.tv_sec));
  pthread_mutex_lock(philo->print_mutex);
  printf("%d TAKE MUTEX\n", philo->index);
  if (ISDEAD_PTR)
  {
    printf("%d DROP MUTEX IN CONDITION\n", philo->index);
    pthread_mutex_unlock(philo->print_mutex);
    return (1);
  }
  if (!ISDEAD_PTR && state == 0)
    printf("%ld %d has taken a fork\n", curr_time, philo->index);
  else if (!ISDEAD_PTR && state == 1)
    printf("%ld %d is eating\n", curr_time, philo->index);
  else if (!ISDEAD_PTR && state == 2)
    printf("%ld %d is sleeping\n", curr_time, philo->index);
  else if (!ISDEAD_PTR && state == 3)
    printf("%ld %d is thinking\n", curr_time, philo->index);
  else if (!ISDEAD_PTR && state > 3)
  {
    ISDEAD_PTR = 1;
    printf("%ld %d died\n", curr_time, philo->index);
    pthread_mutex_unlock(philo->print_mutex);
    return (1);
  }
  if (pthread_mutex_unlock(philo->print_mutex))
    return (1);
  printf("%d DROP MUTEX\n", philo->index);
  return (write(1, "ICI\n", 4), 0);
}

void  ft_usleep(int param)
{
  int i;

  i = 1;
  while (param > (5 * i))
  {
    usleep(5);
    i++;
  }
}

void  maj_time(struct timeval  *time_val, t_philo *philo, int *buffer)
{
  int tmp;

  tmp = ((time_val[1].tv_usec - time_val[0].tv_usec) + \
              (time_val[1].tv_sec - time_val[0].tv_sec));
  philo->time_to_die -= tmp;
  *buffer -= tmp;
}
