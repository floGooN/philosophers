/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:20:21 by florian           #+#    #+#             */
/*   Updated: 2024/07/24 15:57:24 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long int)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	update_time(t_philo *philo)
{
	long int	curr_time;

	curr_time = get_time();
	if (curr_time - philo->time_data.last_time >= philo->time_data.time_to_die)
		return (change_death_status(philo));
	philo->time_data.last_time = curr_time;
	pthread_mutex_lock(philo->shared_mtx.stop_mtx);
	if (*(philo->stop_simu))
	{
		pthread_mutex_unlock(philo->shared_mtx.stop_mtx);
		return (1);
	}
	pthread_mutex_unlock(philo->shared_mtx.stop_mtx);
	return (0);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->shared_mtx.left_fork);
	*(philo->left_fork) = 1;
	pthread_mutex_unlock(philo->shared_mtx.left_fork);
	pthread_mutex_lock(philo->shared_mtx.right_fork);
	philo->right_fork = 1;
	pthread_mutex_unlock(philo->shared_mtx.right_fork);
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

bool	change_death_status(t_philo *philo)
{
	pthread_mutex_lock(philo->shared_mtx.stop_mtx);
	*(philo->stop_simu) = 1;
	pthread_mutex_unlock(philo->shared_mtx.stop_mtx);
	return (1);
}
