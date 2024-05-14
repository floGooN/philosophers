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

/* ====	PROTOTYPES	==== */

bool  print_message(t_philo *philo, int state);
void  ft_usleep(int param);
void  maj_time(struct timeval *time_val, t_philo *philo, int *buffer);

/* ====	PROTOTYPES	==== */
#include <unistd.h>

// void  find_fork(t_philo *philo)
// {
//   int i;
//   int min;
//   int max;

//   min = philo->index - philo->args[0];
//   max = philo->args[0] - philo->index;
//   i = 0;
//   while (!philo[i].left_fork)
//   {
//     pthread_mutex_lock(&philo[i].fork_ptr->fork_mutex);
//     if (!philo[i].fork_ptr->fork)
//     {
//       philo->left_fork = philo[i].fork_ptr;
//       pthread_mutex_unlock(&philo[i].fork_ptr->fork_mutex);
//       break ;
//     }
//     pthread_mutex_unlock(&philo[i].fork_ptr->fork_mutex);
//     if (*(philo[i].is_dead))
//       return ;
//     if ((i + 2) < max)
//       i += 2;
//     else
//       i = min;
//   }
//   i = min;
//   while (!philo[i].right_fork)
//   {
//     pthread_mutex_lock(&philo[i].fork_ptr->fork_mutex);
//     if (!philo[i].fork_ptr->fork)
//     {
//       philo[i].fork_ptr->fork = 1;
//       pthread_mutex_unlock(&philo[i].fork_ptr->fork_mutex);
//       break ;
//     }
//     pthread_mutex_unlock(&philo[i].fork_ptr->fork_mutex);
//     if ((i + 2) < max)
//       i += 2;
//     else
//       i = min;
//   }
// }

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
  struct timeval  time_val[2];

  philo->time_to_die = philo->args[1];
  philo->time_to_eat = philo->args[2];
  print_message(philo, 1);
	while (!ISDEAD_PTR && philo->time_to_die > 0 && philo->time_to_eat > 0)
	{
		gettimeofday(&time_val[0], NULL);
		usleep(10);
		gettimeofday(&time_val[1], NULL);
    maj_time(time_val, philo, &philo->time_to_eat);
	}
  if (ISDEAD_PTR)
    return (1);
  if (philo->time_to_die <= 0)
    return (print_message(philo, 4));
  return (0);
}

bool  sleep_act(t_philo *philo)
{
  struct timeval  time_val[2];

  philo->time_to_sleep = philo->args[3];
  print_message(philo, 2);
	while (!ISDEAD_PTR && philo->time_to_die > 0 && philo->time_to_sleep > 0)
	{
		gettimeofday(&time_val[0], NULL);
		usleep(10);
		gettimeofday(&time_val[1], NULL);
    maj_time(time_val, philo, &philo->time_to_sleep);
	}
  if (ISDEAD_PTR)
    return (1);
  if (philo->time_to_die <= 0)
    return (print_message(philo, 4));
  return (0);
}
