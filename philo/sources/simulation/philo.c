/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:21:00 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/04 13:16:31 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "stdio.h"
#include <unistd.h>
#include <sys/time.h>

/* ====	PROTOTYPES	==== */

bool  print_message(t_philo *philo, int state);
void  ft_usleep(int param);
void  maj_time(struct timeval  *time_val, t_philo *philo, int *buffer);

/* ====	PROTOTYPES	==== */

bool  eat_routine(t_philo *philo)
{
  struct timeval  time_val[2];

  philo->time_to_die = philo->args[1];
  philo->time_to_eat = philo->args[2];
	while (philo->time_to_eat > 0 || philo->time_to_die > 0 || !philo->ret_value)
	{
		gettimeofday(&time_val[0], NULL);
		ft_usleep(10);
		gettimeofday(&time_val[1], NULL);
    maj_time(time_val, philo, &philo->time_to_eat);
	}
  if (philo->ret_value)
    return (1);
  else if (philo->time_to_die <= 0)
    return (print_message(philo, 4));
  else
    return (print_message(philo, 1));
}

bool  sleep_routine(t_philo *philo)
{
  struct timeval  time_val[2];

  philo->time_to_sleep = philo->args[3];
	while (philo->time_to_sleep > 0 || philo->time_to_die > 0 || !philo->ret_value)
	{
		gettimeofday(&time_val[0], NULL);
		ft_usleep(10);
		gettimeofday(&time_val[1], NULL);
    maj_time(time_val, philo, &philo->time_to_sleep);
	}
  if (philo->ret_value)
    return (1);
  else if (philo->time_to_die <= 0)
    return (print_message(philo, 4));
  else
    return (print_message(philo, 2));
}

// void *think_routine(void *arg)
// {
//   t_philo         *lst;
//   lst = (t_philo *) arg;
//   pthread_mutex_lock(&((t_philo *)arg)->shared_mutex[0]);
//   printf("thread nb %ld, index = %d from think\n", lst->index, lst->index);
//   pthread_mutex_unlock(&lst->shared_mutex[0]);
//   return (NULL);
// }

void  *odd_routine(void *arg)
{
  t_philo *curr_philo;

  curr_philo = (t_philo *) arg;
  while (1)
  {
    pthread_mutex_lock(curr_philo->ready_mutex);
    if (curr_philo->ready)
      break ;
    else
      pthread_mutex_unlock(curr_philo->ready_mutex);
  }
  pthread_mutex_unlock(curr_philo->ready_mutex);

  gettimeofday(&curr_philo->philo_tv, NULL);
  while (curr_philo->time_to_die > 0 && !curr_philo->ret_value)
  {
    if (curr_philo->time_to_die > 0 && !curr_philo->ret_value)
      if (eat_routine(curr_philo))
        return (NULL);
    if (curr_philo->time_to_die > 0 && !curr_philo->ret_value)
      if (sleep_routine(curr_philo))
        return (NULL);
  }
  return (NULL);
}

void  *even_routine(void *arg)
{
  t_philo *curr_philo;

  curr_philo = (t_philo *) arg;
  while (1)
  {
    pthread_mutex_lock(curr_philo->ready_mutex);
    if (curr_philo->ready)
      break ;
    else
      pthread_mutex_unlock(curr_philo->ready_mutex);
  }
  pthread_mutex_unlock(curr_philo->ready_mutex);

  gettimeofday(&curr_philo->philo_tv, NULL);
  while (curr_philo->time_to_die > 0 && !curr_philo->ret_value)
  {
    if (curr_philo->time_to_die > 0)
      if (sleep_routine(curr_philo))
        return (NULL);
    if (curr_philo->time_to_die > 0)
      if (eat_routine(curr_philo))
        return (NULL);
  }
  return (NULL);
}
