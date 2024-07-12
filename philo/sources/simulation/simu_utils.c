/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:59:16 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/12 12:13:50 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "stdio.h"
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

#include "action.h"

bool  check_death(t_philo *philo)
{
    pthread_mutex_lock(philo->isdead_mutex);
    if (ISDEAD_PTR)
    {
      pthread_mutex_unlock(philo->isdead_mutex);
      return (1);
    }
    pthread_mutex_unlock(philo->isdead_mutex);
    return (0);
}

long int  get_time(void)
{
	struct timeval	tv;
	
	if (gettimeofday(&tv, NULL))
		return (print_error("gettimeofday() FAILURE\n"), -1);
	return ((long) (tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(int time)
{
	long int	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return(0);
}

bool  change_death_status(t_philo *philo)
{
  pthread_mutex_lock(philo->isdead_mutex);
  if (!*(philo->is_dead))
  {
    *(philo->is_dead) = 1;
    return (pthread_mutex_unlock(philo->isdead_mutex), 0);
  }
  else
    return (pthread_mutex_unlock(philo->isdead_mutex), 1);
}

bool  print_message(t_philo *philo, int action)
{
  long int  curr_time;
  long int  tmp;

  tmp = get_time();
  curr_time = tmp - philo->time_data.start_time;
  if (pthread_mutex_lock(philo->print_mutex))
    return (print_error ("error -> failure to take print_mutex\n"));
  if (check_death(philo))
    return (pthread_mutex_unlock(philo->print_mutex), 1);
  
  // PRINT FUNCTION
  if (action == 0)
    printf("%ld %d has taken a fork\n", curr_time, philo->index);
  else if (action == 1)
    printf("%ld %d is eating\n", curr_time, philo->index);
  else if (action == 2)
    printf("%ld %d is sleeping\n", curr_time, philo->index);
  else if (action == 3)
    printf("%ld %d is thinking\n", curr_time, philo->index);
  else if (action > 3)
  {
    if (change_death_status(philo))
      return (pthread_mutex_unlock(philo->print_mutex), 1);
    printf("%ld %d died\n", curr_time, philo->index);
    return (pthread_mutex_unlock(philo->print_mutex), 1);  
  }
  // PRINT FUNCTION
  
  if (pthread_mutex_unlock(philo->print_mutex))
    return (print_error("error -> failure to drop print_mutex\n"), 1);
  return (0);
}
