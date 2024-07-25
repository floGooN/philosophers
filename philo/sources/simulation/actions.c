/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:20:21 by florian           #+#    #+#             */
/*   Updated: 2024/07/25 17:19:36 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static inline long int  get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long int)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	update_time(t_philo *philo)
{
	const long int	curr_time = get_time();

	if (curr_time - philo->time_data.last_time >= philo->time_data.time_to_die)
        *(philo->shared_res.stop_simu) = 1;
    else
	    philo->time_data.last_time = curr_time;
}

void	drop_forks(t_philo *philo)
{
    pthread_mutex_lock(philo->shared_mtx.r_fork_mtx);
	philo->shared_res.right_fork = 1;
    pthread_mutex_unlock(philo->shared_mtx.r_fork_mtx);
    pthread_mutex_lock(philo->shared_mtx.l_fork_mtx);
	*(philo->shared_res.left_fork) = 1;
    pthread_mutex_unlock(philo->shared_mtx.l_fork_mtx);
    if (philo->time_data.nb_meal > 0)
        philo->time_data.nb_meal--;
	return ;
}

void	ft_usleep(long int time, atomic_int *stop)
{
	const long int	start = get_time();

	while ((get_time() - start) < time)
    {
        if (!*(stop))
		    usleep(time / 10);
        else
            return ;
    }
}

void    wait_everybody(t_philo *philo)
{
    pthread_mutex_lock(philo->shared_mtx.print_mtx);
	if (*(philo->shared_res.stop_simu) == 1)
	{
		pthread_mutex_unlock(philo->shared_mtx.print_mtx);
		return ;
	}
	printf("%ld %d is sleeping\n", get_time() - philo->time_data.start_time,
		philo->index);
	pthread_mutex_unlock(philo->shared_mtx.print_mtx);
	ft_usleep(philo->time_data.time_to_sleep, philo->shared_res.stop_simu);
}
