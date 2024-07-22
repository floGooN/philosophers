/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:20:21 by florian           #+#    #+#             */
/*   Updated: 2024/07/22 13:28:57 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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
