/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:59:16 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/03 14:20:07 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "stdio.h"
#include <unistd.h>
#include <sys/time.h>

bool  print_message(t_philo *philo, int state)
{
  static long int       curr_time;
  static struct timeval tv;

  gettimeofday(&tv, NULL);
  curr_time = ((tv.tv_usec - philo->philo_tv.tv_usec) + (tv.tv_sec - philo->philo_tv.tv_sec));
  pthread_mutex_lock(philo->print_mutex);
  if (state == 0)
    printf("%ld %zu has taken a fork\n", curr_time, philo->index);
  else if (state == 1)
    printf("%ld %zu is eating\n", curr_time, philo->index);
  else if (state == 2)
    printf("%ld %zu is sleeping\n", curr_time, philo->index);
  else if (state == 3)
    printf("%ld %zu is thinkink\n", curr_time, philo->index);
  else
    printf("%ld %ld died\n", curr_time, philo->index);
  if (state <= 3)
  {
    pthread_mutex_unlock(philo->print_mutex);
    return (NULL);
  }
  else
    return (philo->print_mutex);
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
