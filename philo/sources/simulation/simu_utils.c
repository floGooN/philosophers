/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:59:16 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/21 13:27:34 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	change_death_status(t_philo *philo)
{
	pthread_mutex_lock(philo->shared_mtx.stop_mtx);
	*(philo->stop_simu) = 1;
	pthread_mutex_unlock(philo->shared_mtx.stop_mtx);
	return (1);
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
	if (curr_time - philo->time_data.last_time >= philo->time_data.time_to_die)
		return (change_death_status(philo));
	philo->time_data.last_time = curr_time;
	return (0);
}
