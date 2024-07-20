/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:59:16 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/20 19:07:43 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	change_death_status(t_philo *philo)
{
	pthread_mutex_lock(philo->shared_mtx.isdead_mtx);
	*(philo->is_dead) = 1;
	pthread_mutex_unlock(philo->shared_mtx.isdead_mtx);
	return (0);
}

bool	check_death(t_philo *philo)
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
	if (curr_time - philo->time_data.last_time >= philo->time_data.death_time)
		return (print_message("died", philo, 1));
	philo->time_data.last_time = curr_time;
	return (0);
}
