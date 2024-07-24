/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:59:16 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/24 15:57:38 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void    print_end(t_philo *philo)
{
    pthread_mutex_lock(philo->shared_mtx.print_mtx);
    printf("\n**********************************\n");
    printf("*                                *\n");
    printf("*   THE SIMULATION IS COMPLETE   *\n");
    printf("*                                *\n");
    printf("**********************************\n\n");
    pthread_mutex_unlock(philo->shared_mtx.print_mtx);
}

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
    if (philo->time_data.nb_meal > 0)
    {
	    *(philo->counter) += 1;
        pthread_mutex_lock(philo->shared_mtx.stop_mtx);
        *(philo->stop_simu) = 1;
        pthread_mutex_unlock(philo->shared_mtx.stop_mtx);
    }
    else if (philo->time_data.nb_meal == 0)
        *(philo->counter) -= 1;
	if (!*(philo->counter))
	{
        pthread_mutex_lock(philo->shared_mtx.stop_mtx);
        *(philo->stop_simu) = -2;
        pthread_mutex_unlock(philo->shared_mtx.stop_mtx);
        print_end(philo);
		pthread_mutex_unlock(philo->shared_mtx.counter_mtx);
		return (NULL);
	}
	pthread_mutex_unlock(philo->shared_mtx.counter_mtx);
	pthread_mutex_lock(philo->shared_mtx.end_mtx);
	pthread_mutex_unlock(philo->shared_mtx.end_mtx);
    return (NULL);
}
