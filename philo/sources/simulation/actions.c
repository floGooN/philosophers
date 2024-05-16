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

bool      print_message(t_philo *philo, int action);
void      ft_usleep(int time);
long int  get_time(void);
bool      check_death(t_philo *philo);


/* ====	PROTOTYPES	==== */


bool  find_fork(t_philo *philo)
{
  if (philo->index % 2)
  {
    if (pthread_mutex_lock(&philo->fork_mutex))
      return (1); // error taking mutex
    if (print_message(philo, 0))
      return (pthread_mutex_unlock(&philo->fork_mutex), 1);

    if (pthread_mutex_lock(&philo[philo->index + 1].fork_mutex))
      return (1); // error taking mutex
    if (print_message(philo, 0))
      return (pthread_mutex_unlock(&philo[philo->index + 1].fork_mutex), \
              pthread_mutex_unlock(&philo->fork_mutex), 1);
  }
  else
  {
    if (pthread_mutex_lock(&philo[philo->index + 1].fork_mutex))
      return (1); // error taking mutex
    if (print_message(philo, 0))
      return (pthread_mutex_unlock(&philo[philo->index + 1].fork_mutex), 1);
    if (pthread_mutex_lock(&philo->fork_mutex))
      return (1); // error taking mutex
    if (print_message(philo, 0))
      return (pthread_mutex_unlock(&philo[philo->index + 1].fork_mutex), \
              pthread_mutex_unlock(&philo->fork_mutex), 1);
  }
  return (0);
}

bool  drop_forks(t_philo *philo)
{
  if (pthread_mutex_unlock(&philo[philo->index + 1].fork_mutex) || \
      pthread_mutex_unlock(&philo->fork_mutex))
    return (1);
  return (0);
}

bool  think_act(void *arg)
{
  t_philo         *philo;

  philo = (t_philo *) arg;
  print_message(philo, 3);
  return (find_fork(philo));
}

bool  eat_act(t_philo *philo)
{
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

  if (check_death(philo))
    return (1);

  if (philo->time_to_die <= 0)
    return (print_message(philo, 4));
  return (drop_forks(philo));
}

bool  sleep_act(t_philo *philo)
{
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

  if (check_death(philo))
    return (1);

  if (philo->time_to_die <= 0)
    return (print_message(philo, 4));
  return (0);
}
