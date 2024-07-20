/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:20:21 by florian           #+#    #+#             */
/*   Updated: 2024/07/20 20:00:34 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	print_message(char *msg, t_philo *philo, bool is_dead)
{
	pthread_mutex_lock(philo->shared_mtx.print_mtx);
	pthread_mutex_lock(philo->shared_mtx.isdead_mtx);
    if (*(philo->is_dead))
    {
	    pthread_mutex_unlock(philo->shared_mtx.print_mtx);
	    pthread_mutex_unlock(philo->shared_mtx.isdead_mtx);
        return (1);
    }
    if (is_dead)
        *(philo->is_dead) = 1;
	printf("%ld %d %s\n", get_time() - philo->time_data.start_time,
		philo->index, msg);
	pthread_mutex_unlock(philo->shared_mtx.print_mtx);
	pthread_mutex_unlock(philo->shared_mtx.isdead_mtx);
    if (is_dead)
        return (1);
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

bool    take_right(t_philo *philo, bool take_for_real)
{
    while (take_for_real)
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
            philo->time_data.death_time)
            return (print_message("died", philo, 1), 1);
        usleep(100);
    }
    return (0);
}

bool	take_forks(t_philo *philo)
{
    take_right(philo, 1);
    while (1)
    {
        pthread_mutex_lock(philo->shared_mtx.left_fork);
        if (!*(philo->left_fork))
        {
            pthread_mutex_unlock(philo->shared_mtx.left_fork);
            drop_a_fork(philo, philo->shared_mtx.right_fork, &philo->right_fork);
            if (take_right(philo, 0))
                return (1);
        }
        else
        {
            if (print_message("has taken a fork", philo, 0))
                return (pthread_mutex_unlock(philo->shared_mtx.left_fork), 1);
            *(philo->left_fork) = 0;
            pthread_mutex_unlock(philo->shared_mtx.left_fork);
            break ;
        }
    }
	return (print_message("has taken a fork", philo, 0));
}
