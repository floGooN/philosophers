/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:20:21 by florian           #+#    #+#             */
/*   Updated: 2024/07/24 20:03:09 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static inline long int  get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long int)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int print_death(t_philo *philo)
{
    pthread_mutex_lock(philo->shared_mtx.print_mtx);
    if (*(philo->shared_res.stop_simu) == 0)
        *(philo->shared_res.stop_simu) = 1;
    else
        return (pthread_mutex_unlock(philo->shared_mtx.print_mtx), 1);
    printf("%ld %d died\n", get_time() - philo->time_data.start_time, \
                                                        philo->index);
    return (pthread_mutex_unlock(philo->shared_mtx.print_mtx), 1);
}

int	update_time(t_philo *philo)
{
	long int	curr_time;

	curr_time = get_time();
	if (curr_time - philo->time_data.last_time >= philo->time_data.time_to_die)
        return (print_death(philo));
	philo->time_data.last_time = curr_time;
	return (0);
}

void	drop_forks(t_philo *philo)
{
    pthread_mutex_lock(philo->shared_mtx.l_fork_mtx);
	*(philo->shared_res.left_fork) = 1;
    pthread_mutex_unlock(philo->shared_mtx.l_fork_mtx);
    pthread_mutex_lock(philo->shared_mtx.r_fork_mtx);
	philo->shared_res.right_fork = 1;
    pthread_mutex_unlock(philo->shared_mtx.r_fork_mtx);
	if (philo->time_data.nb_meal > 0)
		(philo->time_data.nb_meal)--;
	return ;
}

void	ft_usleep(long int time)
{
	const long int	start = get_time();

	while ((get_time() - start) < time)
		usleep(time / 10);
}
