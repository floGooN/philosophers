/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:21:00 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/17 17:31:21 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <struct.h>
#include <philo.h>

static int  wait_loop(t_philo *philo)
{
  while (1)
  {
    if (pthread_mutex_lock(philo->shared_mtx.ready_mtx))
        return (ft_perror("error -> lock mtx (wait_loop)\n"), 1);
    if (*(philo->ready))
    {
      	if (pthread_mutex_unlock(philo->shared_mtx.ready_mtx))
            return (ft_perror("error -> unlock mtx (wait_loop)\n"), 1);
      	return (0);
    }
    if (pthread_mutex_unlock(philo->shared_mtx.ready_mtx))
        return (ft_perror("error -> unlock mtx (wait_loop)\n"), 1);
  }
  return (0);
}

void  *odd_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *) arg;
    if (wait_loop(philo))
        return (stop_simu(philo, NULL), NULL);
    philo->time_data.start_time = get_time();
    if (philo->time_data.start_time < 0)
      return (stop_simu(philo, NULL), NULL);
    philo->time_data.last_time = philo->time_data.start_time;
    while (!check_death(philo))
    {
        if (think_act(philo))
          break ;
        if (eat_act(philo))
          break ;
        // if (philo->nb_meal == 0)
        //   break ;
        if (sleep_act(philo))
          break ;
    }
    // check if is dead else is_dead == 1
    return (NULL);
}

void  *even_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *) arg;
    if (wait_loop(philo))
        return (stop_simu(philo, NULL), NULL);
    philo->time_data.start_time = get_time();
    if (philo->time_data.start_time < 0)
      return (stop_simu(philo, NULL), NULL);
    philo->time_data.last_time = philo->time_data.start_time;
    while (!check_death(philo))
    {
      if (sleep_act(philo))
        break ;
      if (think_act(philo))
        break ;
      if (eat_act(philo))
        break ;
      // if (philo->nb_meal == 0)
      //   break ;
    }
    // check if is dead else is_dead == 1
    return (NULL);
}
