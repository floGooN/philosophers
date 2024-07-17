/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:59:16 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/17 13:36:45 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool  change_death_status(t_philo *philo)
{
  pthread_mutex_lock(philo->shared_mtx.isdead_mtx);
    *(philo->is_dead) = 1;
  return (pthread_mutex_unlock(philo->shared_mtx.isdead_mtx), 0);
}

bool  check_death(t_philo *philo)
{
    pthread_mutex_lock(philo->shared_mtx.isdead_mtx);
    if (*(philo->is_dead))
    {
      pthread_mutex_unlock(philo->shared_mtx.isdead_mtx);
      return (1);
    }
    return (pthread_mutex_unlock(philo->shared_mtx.isdead_mtx));
}

long int  get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (ft_perror("gettimeofday() FAILURE\n"), -1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void    ft_usleep(long time)
{
    long int	start;

    start = get_time();
    while ((get_time() - start) < time)
        usleep(time / 10);
}

int			update_time(t_philo *philo, long int time)
{
    long int  curr_time;

    curr_time = get_time();
    if (curr_time == -1)
        return (1);
    philo->time_data.time_to_die -= curr_time - time;
    if (philo->time_data.time_to_die < 0)
    {
        if (change_death_status(philo))
            return (1);
        if (print_message(philo, 4))
            return (1);
        return (1);
    }
    return (0);
}