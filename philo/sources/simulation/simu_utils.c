/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:59:16 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/18 17:41:05 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool  change_death_status(t_philo *philo)
{
    if (pthread_mutex_lock(philo->shared_mtx.isdead_mtx))
        return (ft_perror("error -> lock mtx change_death_status\n"), 1);
    *(philo->is_dead) = 1;
    if (pthread_mutex_unlock(philo->shared_mtx.isdead_mtx))
        return (ft_perror("error -> unlock mtx change_death_status\n"), 1);
    return (0);
}

bool  check_death(t_philo *philo)
{
    if (pthread_mutex_lock(philo->shared_mtx.isdead_mtx))
        return (ft_perror("error -> lock mtx check_death\n"), 1);
    if (*(philo->is_dead))
    {
      if (pthread_mutex_unlock(philo->shared_mtx.isdead_mtx))
        ft_perror("error -> unlock mtx check_death\n");
      return (1);
    }
    if (pthread_mutex_unlock(philo->shared_mtx.isdead_mtx))
        return (ft_perror("error -> unlock mtx check_death\n"), 1);
    return (0);
}

long int  get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (ft_perror("gettimeofday() FAILURE\n"), -1);
	return ((long int) (tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void    ft_usleep(long int time)
{
    const long int	start = get_time();

    while ((get_time() - start) < time)
        usleep(time / 10);
}

int update_time(t_philo *philo)
{
    long int    curr_time;

    curr_time = get_time();
    if (curr_time == -1)
        return (-1);
    if (curr_time - philo->time_data.last_time >= philo->time_data.death_time)
        return (1);
    philo->time_data.last_time = curr_time;
    return (0);
}
