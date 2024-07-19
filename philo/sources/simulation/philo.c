/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:21:00 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/19 15:55:46 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
bool  take_forks(t_philo *philo);
bool  drop_forks(t_philo *philo);

static void ft_usleep(long int time)
{
    const long int	start = get_time();

    while ((get_time() - start) < time)
        usleep(time / 10);
}

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
    if (philo->index % 2)
        usleep(500);
    philo->time_data.start_time = get_time();
    philo->time_data.last_time = philo->time_data.start_time;
    return (0);
}

void  *odd_routine(void *arg)
{
    t_philo *philo = (t_philo *) arg;

    if (init_routine(philo))
      return (stop_simu(philo, NULL), NULL);
    while (1)
    {
        if (take_forks(philo))
            return (stop_simu(philo, NULL), NULL);
        if (update_time(philo))
            return (stop_simu(philo, NULL), NULL);
        if (print_message("is eating", philo, 0))
            return (stop_simu(philo, NULL), NULL);
        ft_usleep(philo->time_data.time_to_eat);
        if (drop_forks(philo))
            return (stop_simu(philo, NULL), NULL);
        if (print_message("is sleeping", philo, 0))
            return (stop_simu(philo, NULL), NULL);
        ft_usleep(philo->time_data.time_to_sleep);
    }
    return (NULL);
}

void  *even_routine(void *arg)
{
    t_philo *philo = (t_philo *) arg;

    if (init_routine(philo))
      return (stop_simu(philo, NULL), NULL);
    while (1)
    {
        if (print_message("is sleeping", philo, 0))
            return (stop_simu(philo, NULL), NULL);
        ft_usleep(philo->time_data.time_to_sleep);
        if (take_forks(philo))
            return (stop_simu(philo, NULL), NULL);
        if (update_time(philo))
            return (stop_simu(philo, NULL), NULL);
        if (print_message("is eating", philo, 0))
            return (stop_simu(philo, NULL), NULL);
        ft_usleep(philo->time_data.time_to_eat);
        if (drop_forks(philo))
            return (stop_simu(philo, NULL), NULL);
        if (update_time(philo))
            return (stop_simu(philo, NULL), NULL);
    }
    return (NULL);
}
