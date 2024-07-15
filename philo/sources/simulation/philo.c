/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:21:00 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/15 16:55:42 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <struct.h>
#include <philo.h>

static void wait_loop(t_philo *philo)
{
  while (1)
  {
    pthread_mutex_lock(philo->ready_mutex);
    if (*(philo->ready))
    {
      	pthread_mutex_unlock(philo->ready_mutex);
      	return ;
    }
    pthread_mutex_unlock(philo->ready_mutex);
  }
}

void  *odd_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *) arg;
    wait_loop(philo);
    // GET_TIME(philo->time_data.start_time);
    philo->time_data.start_time = get_time();
    while (1)
    {
        if (check_death(philo) || think_act(philo))
        break;
        if (check_death(philo) || eat_act(philo))
        break;
        if (check_death(philo) || sleep_act(philo))
        break;
        // if (philo->nb_meal == 0)
        //   break ;
    }
    return (NULL);
}

void  *even_routine(void *arg)
{
	t_philo *philo;

  	philo = (t_philo *) arg;
	  wait_loop(philo);
    // GET_TIME(philo->time_data.start_time);
    philo->time_data.start_time = get_time();
	while (1)
  	{
		if (check_death(philo) || sleep_act(philo))
		  break;
		if (check_death(philo) || think_act(philo))
		  break;
		// if (philo->nb_meal == 0)
		//   break ;
		if (check_death(philo) || eat_act(philo))
		    break;
	}
	return (NULL);
}
