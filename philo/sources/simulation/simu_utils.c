/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:59:16 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/16 19:14:26 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/*
    * check if ANOTHER philo is dead
*/
bool  check_death(t_philo *philo)
{
    pthread_mutex_lock(philo->shared_mtx.isdead_mtx);
    if (*(philo->is_dead))
    {
      pthread_mutex_unlock(philo->shared_mtx.isdead_mtx);
      return (1);
    }
    pthread_mutex_unlock(philo->shared_mtx.isdead_mtx);
    return (0);
}

/*
    *
*/
static bool  change_death_status(t_philo *philo)
{
  pthread_mutex_lock(philo->shared_mtx.isdead_mtx);
    *(philo->is_dead) = 1;
  return (pthread_mutex_unlock(philo->shared_mtx.isdead_mtx), 0);
}


long int    get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (print_error("gettimeofday() FAILURE\n"), -1);
	return ((long int) (tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void    ft_usleep(long int time)
{
    const long int	start = get_time();

    while ((get_time() - start) < time)
        usleep(time / 10);
}

int    wait_for_print(t_philo *philo)
{
    while (!check_death(philo))
    {
        if (pthread_mutex_lock(philo->shared_mtx.prt_mtx_watch))
            return (print_error("error -> lock mtx\n"), 1);
        if (*(philo->print))
            return (pthread_mutex_unlock(philo->shared_mtx.prt_mtx_watch));
        if (pthread_mutex_unlock(philo->shared_mtx.prt_mtx_watch))
            return (print_error("error -> unlock mtx\n"), 1);
    }
    return (0);
}

int take_print_mtx(t_philo *philo)
{
    if (pthread_mutex_lock(philo->shared_mtx.print_mtx))
      return (print_error("error -> lock print_mutex\n"), 1);
    if (pthread_mutex_lock(philo->shared_mtx.prt_mtx_watch))
      return (print_error("error -> lock print_mutex\n"), 1);
    *(philo->print) = 0;
    return (pthread_mutex_unlock(philo->shared_mtx.prt_mtx_watch));
}

int drop_print_mutex(t_philo *philo)
{
    if (pthread_mutex_unlock(philo->shared_mtx.print_mtx))
    {
        pthread_mutex_lock(philo->shared_mtx.prt_mtx_watch);
        *(philo->print) = 1;
        pthread_mutex_unlock(philo->shared_mtx.prt_mtx_watch);
        return (1);
    }
    if (pthread_mutex_lock(philo->shared_mtx.prt_mtx_watch))
        return (print_error("error -> unlock print mtx\n"), 1);
    *(philo->print) = 1;
    return (pthread_mutex_unlock(philo->shared_mtx.prt_mtx_watch));
}

bool  print_message(t_philo *philo, int action)
{
    long int  curr_time;
    const long int  time = get_time();

    if (wait_for_print(philo))
        return (1);
    if (take_print_mtx(philo))
        return (1);
    if (check_death(philo))
      return (drop_print_mutex(philo), 1);

    curr_time = time - philo->time_data.start_time;
    philo->time_data.time_to_die -= get_time() - time;

    if (philo->time_data.time_to_die <= 0)
      action = 4;
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
      change_death_status(philo);
      printf("%ld %d died\n", curr_time, philo->index);
      return (drop_print_mutex(philo), 1);
    }
    // PRINT FUNCTION
    return (drop_print_mutex(philo));
}
