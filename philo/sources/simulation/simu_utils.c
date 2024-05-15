/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:59:16 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/15 15:20:00 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "stdio.h"
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

#include "action.h"

long int  get_time(void);

bool  print_message(t_philo *philo, int state)
{
  long int        curr_time;
  struct timeval  tv;
  long int        tmp1;

  tmp1 = get_time();
  curr_time = tmp1 - philo->start_time;
  if (pthread_mutex_lock(philo->print_mutex))
    return (print_error("FAIL TAKE MUTEX\n"));
  if (ISDEAD_PTR)
  {
    printf("%d DROP MUTEX IN DEAD CONDITION\n", philo->index);
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
    return (print_error("FAIL DROP MUTEX\n"), 1);
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
