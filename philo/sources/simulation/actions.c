/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:20:21 by florian           #+#    #+#             */
/*   Updated: 2024/07/21 13:41:49 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	print_message(char *msg, t_philo *philo)
{
	pthread_mutex_lock(philo->shared_mtx.print_mtx);
	pthread_mutex_lock(philo->shared_mtx.stop_mtx);
    if (*(philo->stop_simu))
    {
	    pthread_mutex_unlock(philo->shared_mtx.print_mtx);
	    pthread_mutex_unlock(philo->shared_mtx.stop_mtx);
        return (1);
    }
	pthread_mutex_unlock(philo->shared_mtx.stop_mtx);
	printf("%ld %d %s\n", get_time() - philo->time_data.start_time, \
		philo->index, msg);
	pthread_mutex_unlock(philo->shared_mtx.print_mtx);
	return (0);
}

bool	drop_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->shared_mtx.right_fork);
	pthread_mutex_lock(philo->shared_mtx.left_fork);
	philo->right_fork = 1;
	*(philo->left_fork) = 1;
	pthread_mutex_unlock(philo->shared_mtx.right_fork);
	pthread_mutex_unlock(philo->shared_mtx.left_fork);
	if (philo->time_data.nb_meal > 0)
		(philo->time_data.nb_meal)--;
	return (0);
}

void    drop_a_fork(t_philo *philo, pthread_mutex_t *fork_mtx, bool *fork)
{
    pthread_mutex_lock(fork_mtx);
    *fork = 0;
    pthread_mutex_unlock(fork_mtx);
}

bool    take_right(t_philo *philo)
{
    while (1)
    {
        pthread_mutex_lock(philo->shared_mtx.right_fork);
        if (philo->right_fork)
        {
            philo->right_fork = 0;
            pthread_mutex_unlock(philo->shared_mtx.right_fork);
            return (0);
        }
        pthread_mutex_unlock(philo->shared_mtx.right_fork);
        if (get_time() - philo->time_data.last_time >= \
            philo->time_data.time_to_die)
            return (change_death_status(philo));
        usleep(100);
    }
    return (0);
}

bool	take_forks(t_philo *philo)
{
    if (take_right(philo))
        return (1);
    while (1)
    {
        pthread_mutex_lock(philo->shared_mtx.left_fork);
        if (!*(philo->left_fork))
        {
            pthread_mutex_unlock(philo->shared_mtx.left_fork);
            // drop_a_fork(philo, philo->shared_mtx.right_fork, &philo->right_fork);
            // if (take_right(philo))
            //     return (1);
        }
        else
        {
            if (print_message("has taken a fork", philo))
                return (pthread_mutex_unlock(philo->shared_mtx.left_fork), 1);
            *(philo->left_fork) = 0;
            pthread_mutex_unlock(philo->shared_mtx.left_fork);
            break ;
        }
    }
	return (print_message("has taken a fork", philo));
}
