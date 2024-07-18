/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:21:00 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/18 13:11:35 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
bool  take_forks(t_philo *philo);
bool  drop_forks(t_philo *philo);

static int  wait_loop(t_philo *philo)
{
  while (!check_death(philo))
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
    usleep(100);
  }
  return (1);
}

static int  init_routine(t_philo *philo)
{
    if (wait_loop(philo))
        return (1);
    philo->time_data.start_time = get_time();
    if (philo->time_data.start_time < 0)
      return (1);
    philo->time_data.last_time = philo->time_data.start_time;
    return (0);
}

void  *odd_routine(void *arg)
{
    t_philo *philo = (t_philo *) arg;
    long int      ret_value;

    if (init_routine(philo))
      return (stop_simu(philo, NULL), NULL);
    while (1)
    {
      // think_act
      if (print_message("is thinking", philo, 0))
        return (stop_simu(philo, NULL), NULL);
      take_forks(philo);



      //eat_act
      ret_value = update_time(philo);
      if (ret_value)
      {
          if (ret_value == -1)
              return (stop_simu(philo, NULL), NULL);
          else
          {
            if (print_message("died", philo, 1))
              return (stop_simu(philo, NULL), NULL);
          } 
      }
      if (print_message("is eating", philo, 0))
          return (stop_simu(philo, NULL), NULL);
      ft_usleep(philo->time_data.time_to_eat);
      drop_forks(philo);
        // if (philo->nb_meal == 0)
        //   break ;



      // sleep_act
      if (print_message("is sleeping", philo, 0))
        return (stop_simu(philo, NULL), NULL);
      ft_usleep(philo->time_data.time_to_sleep);
    }
    // check if is dead else is_dead == 1
    return (NULL);
}

void  *even_routine(void *arg)
{
    t_philo *philo = (t_philo *) arg;
    long int      ret_value;

    if (init_routine(philo))
      return (stop_simu(philo, NULL), NULL);
    while (1)
    {
      // sleep_act
      if (print_message("is sleeping", philo, 0))
        return (stop_simu(philo, NULL), NULL);
      ft_usleep(philo->time_data.time_to_sleep);



      // think_act
      if (print_message("is thinking", philo, 0))
        return (stop_simu(philo, NULL), NULL);
      take_forks(philo);


      
      //eat_act
      ret_value = update_time(philo);
      if (ret_value)
      {
          if (ret_value == -1)
              return (stop_simu(philo, NULL), NULL);
          else
          {
            if (print_message("died", philo, 1))
              return (stop_simu(philo, NULL), NULL);
          } 
      }
      if (print_message("is eating", philo, 0))
          return (stop_simu(philo, NULL), NULL);
      ft_usleep(philo->time_data.time_to_eat);
      drop_forks(philo);
      // if (philo->nb_meal == 0)
      //   break ;
    }
    // check if is dead else is_dead == 1
    return (NULL);
}
