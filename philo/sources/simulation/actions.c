/*
  * HEADER_42
  * HEADER_42
  * HEADER_42
  * HEADER_42
*/

#include "struct.h"
#include "stdio.h"
#include <sys/time.h>

#include "action.h"
#include <unistd.h>

/* ====	PROTOTYPES	==== */

bool      print_message(t_philo *philo, int state);
void      ft_usleep(int time);
long int  get_time(void);

/* ====	PROTOTYPES	==== */

// bool  think_act(void *arg)
// {
//   t_philo         *philo;
//   struct timeval  time_val[2];

//   philo = (t_philo *) arg;
//   print_message(philo, 3);
//   find_fork(philo);
//   return (0);
// }

bool  eat_act(t_philo *philo)
{
  struct timeval  time_val0;
  struct timeval  time_val1;
  long int        time1;
  long int        time2;

  philo->time_to_die = philo->args[1];
  philo->time_to_eat = philo->args[2];
  if (print_message(philo, 1))
    return (1);
  time1 = get_time();
  ft_usleep(philo->time_to_eat);
  time2 = get_time();
  philo->time_to_die -= time2 - time1;
  philo->time_to_eat -= time2 - time1;
  pthread_mutex_lock(philo->isdead_mutex);
  if (ISDEAD_PTR)
  {
    pthread_mutex_unlock(philo->isdead_mutex);
    return (1);
  }
  pthread_mutex_unlock(philo->isdead_mutex);
  if (philo->time_to_die <= 0)
    return (print_message(philo, 4));
  return (0);
}

bool  sleep_act(t_philo *philo)
{
  struct timeval  time_val0;
  struct timeval  time_val1;
  long int        time1;
  long int        time2;

  philo->time_to_sleep = philo->args[3];
  if (print_message(philo, 2))
    return (1);
  time1 = get_time();
  ft_usleep(philo->time_to_sleep);
  time2 = get_time();
  philo->time_to_die -= time2 - time1;
  philo->time_to_sleep -= time2 - time1;
  pthread_mutex_lock(philo->isdead_mutex);
  if (ISDEAD_PTR)
  {
    pthread_mutex_unlock(philo->isdead_mutex);
    return (1);
  }
  pthread_mutex_unlock(philo->isdead_mutex);
  if (philo->time_to_die <= 0)
    return (print_message(philo, 4));
  return (0);
}
