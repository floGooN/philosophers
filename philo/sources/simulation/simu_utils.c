/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:59:16 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/24 19:20:57 by florian          ###   ########.fr       */
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
    struct timeval  tv;

	pthread_mutex_lock(philo->shared_mtx.ready_mtx);
	pthread_mutex_unlock(philo->shared_mtx.ready_mtx);
	if (philo->index % 2)
		usleep(50 * philo->nb_philo);
	gettimeofday(&tv, NULL);
	philo->time_data.start_time = \
    (long int)(tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	philo->time_data.last_time = philo->time_data.start_time;
}

void	*end_of_loop(t_philo *philo)
{
    if (philo->time_data.nb_meal > 0)
	    *(philo->shared_res.counter) += 1;
    else if (philo->time_data.nb_meal == 0)
        *(philo->shared_res.counter) -= 1;
	if (*(philo->shared_res.counter) == 0)
	{
        *(philo->shared_res.stop_simu) = 1;
        print_end(philo);
	}
	pthread_mutex_lock(philo->shared_mtx.end_mtx);
	pthread_mutex_unlock(philo->shared_mtx.end_mtx);
    return (NULL);
}
