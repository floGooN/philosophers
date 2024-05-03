/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:21:00 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/03 14:19:19 by fberthou         ###   ########.fr       */
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

bool  eat_routine(t_philo *lst)
{
  struct timeval  time_val[2];

  lst->time_to_die = lst->args[1];
  lst->time_to_eat = lst->args[2];
	while (lst->time_to_eat > 0 && lst->time_to_die > 0)
	{
		gettimeofday(&time_val[0], NULL);
		ft_usleep(10);
		gettimeofday(&time_val[1], NULL);
    maj_time(time_val, lst, &lst->time_to_eat);
	}
  if (lst->time_to_die <= 0)
    return (print_message(lst, 4));
  else
    return (print_message(lst, 1));
}

bool  sleep_routine(t_philo *lst)
{
  struct timeval  time_val[2];

  lst->time_to_sleep = lst->args[3];
	while (lst->time_to_sleep > 0 && lst->time_to_die > 0)
	{
		gettimeofday(&time_val[0], NULL);
		ft_usleep(10);
		gettimeofday(&time_val[1], NULL);
    maj_time(time_val, lst, &lst->time_to_sleep);
	}
  if (lst->time_to_die <= 0)
    return (print_message(lst, 4));
  else
    return (print_message(lst, 2));
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

void  *routine_b(void *arg)
{
  t_philo *curr_philo;

  curr_philo = (t_philo *) arg;
  gettimeofday(&curr_philo->philo_tv, NULL);
  while (curr_philo->time_to_die)
  {
    if (curr_philo->time_to_die > 0)
      if (eat_routine(curr_philo))
        break ;
    if (curr_philo->time_to_die > 0)
      if (sleep_routine(curr_philo))
        break ;
  }
  return (curr_philo->print_mutex);
}

void  *routine_a(void *arg)
{
  t_philo *curr_philo;

  curr_philo = (t_philo *) arg;
  gettimeofday(&curr_philo->philo_tv, NULL);
  while (curr_philo->time_to_die)
  {
    if (curr_philo->time_to_die > 0)
      if (sleep_routine(curr_philo))
        break ;
    if (curr_philo->time_to_die > 0)
      if (eat_routine(curr_philo))
        break ;
  }
  return (curr_philo->print_mutex);
}