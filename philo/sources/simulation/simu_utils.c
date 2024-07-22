/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:59:16 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/22 13:28:11 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	wait_everybody_pls(t_philo *philo)
{
	pthread_mutex_lock(philo->shared_mtx.ready_mtx);
	pthread_mutex_unlock(philo->shared_mtx.ready_mtx);
	if (philo->index % 2)
		usleep(20 * philo->nb_philo);
	philo->time_data.start_time = get_time();
	philo->time_data.last_time = philo->time_data.start_time;
}

void	*end_of_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->shared_mtx.counter_mtx);
	*(philo->counter) -= 1;
	if (!*(philo->counter))
	{
		pthread_mutex_lock(philo->shared_mtx.print_mtx);
		printf("\n******************************\n");
		printf("*                            *\n");
		printf("*   THE SIMULATION IS OVER   *\n");
		printf("*                            *\n");
		printf("******************************\n\n");
		pthread_mutex_unlock(philo->shared_mtx.print_mtx);
		pthread_mutex_unlock(philo->shared_mtx.counter_mtx);
		return (NULL);
	}
	pthread_mutex_unlock(philo->shared_mtx.counter_mtx);
	return (NULL);
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
	pthread_mutex_lock(philo->shared_mtx.stop_mtx);
	if (*(philo->stop_simu))
	{
		pthread_mutex_unlock(philo->shared_mtx.print_mtx);
		pthread_mutex_unlock(philo->shared_mtx.stop_mtx);
		return (1);
	}
	pthread_mutex_unlock(philo->shared_mtx.stop_mtx);
	return (0);
}
