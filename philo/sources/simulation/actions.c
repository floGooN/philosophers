/*
  * HEADER_42
  * HEADER_42
  * HEADER_42
  * HEADER_42
*/

#include "struct.h"
#include "stdio.h"
#include <sys/time.h>

/* ====	PROTOTYPES	==== */

bool  print_message(t_philo *philo, int state);
void  ft_usleep(int param);
void  maj_time(struct timeval *time_val, t_philo *philo, int *buffer);

/* ====	PROTOTYPES	==== */
#include <unistd.h>

bool  eat_act(t_philo *philo)
{
  struct timeval  time_val[2];

  philo->time_to_die = philo->args[1];
  philo->time_to_eat = philo->args[2];
	while (philo->time_to_eat > 0 && philo->time_to_die > 0 && !*(philo->is_dead))
	{
		gettimeofday(&time_val[0], NULL);
		usleep(10);
		gettimeofday(&time_val[1], NULL);
    maj_time(time_val, philo, &philo->time_to_eat);
	}
  // pthread_mutex_lock(philo->print_mutex);
  // printf("EAT_ACT philo = %d, die = %d, dead = %d\n", philo->index, philo->time_to_die, *(philo->is_dead));
  // pthread_mutex_unlock(philo->print_mutex);
  if (*(philo->is_dead))
    return (1);
  else if (philo->time_to_die <= 0)
    return (print_message(philo, 4));
  else
    return (print_message(philo, 1));
}

bool  sleep_act(t_philo *philo)
{
  struct timeval  time_val[2];

  philo->time_to_sleep = philo->args[3];
	while (philo->time_to_sleep > 0 && philo->time_to_die > 0 && !*(philo->is_dead))
	{
		gettimeofday(&time_val[0], NULL);
		usleep(10);
		gettimeofday(&time_val[1], NULL);
    maj_time(time_val, philo, &philo->time_to_sleep);
	}
  // pthread_mutex_lock(philo->print_mutex);
  // printf("SLEEP_ACT philo = %d, die = %d, dead = %d\n", philo->index, philo->time_to_die, *(philo->is_dead));
  // pthread_mutex_unlock(philo->print_mutex);
  if (*(philo->is_dead))
  {
    return (1);
  }
  else if (philo->time_to_die <= 0)
  {
    // pthread_mutex_lock(philo->print_mutex);
    // printf("philo is_dead = %d\n", philo->index);
    // pthread_mutex_unlock(philo->print_mutex);
    return (print_message(philo, 4));
  }
  else
  {
    // pthread_mutex_lock(philo->print_mutex);
    // printf("philo is ok = %d\n", philo->index);
    // pthread_mutex_unlock(philo->print_mutex);
    return (print_message(philo, 2));
  }
}
