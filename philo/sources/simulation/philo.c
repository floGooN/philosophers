/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:21:00 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/20 20:24:57 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	*end_of_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->shared_mtx.counter_mtx);
	*(philo->monitor_counter) -= 1;
    if (!*(philo->monitor_counter))
    {
        pthread_mutex_lock(philo->shared_mtx.print_mtx);
        printf("\n******************************\n");
        printf("\n*                            *\n");
        printf("\n*   THE SIMULATION IS OVER   *\n");
        printf("\n*                            *\n");
        printf("\n******************************\n\n");
        pthread_mutex_unlock(philo->shared_mtx.print_mtx);
    }
	pthread_mutex_unlock(philo->shared_mtx.counter_mtx);
	return (NULL);
}

static void	ft_usleep(long int time)
{
	const long int	start = get_time();

	while ((get_time() - start) < time)
		usleep(time / 10);
}

static int	wait_everybody_pls(t_philo *philo)
{
    pthread_mutex_lock(philo->shared_mtx.ready_mtx);
    pthread_mutex_unlock(philo->shared_mtx.ready_mtx);
    if (philo->index % 2)
        usleep(20 * philo->nb_philo);
    philo->time_data.start_time = get_time();
    philo->time_data.last_time = philo->time_data.start_time;
	return (1);
}


void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (init_routine(philo))
		return (stop_simu(philo, NULL), NULL);
	while (philo->time_data.nb_meal)
	{
		if (print_message("is thinking", philo, 0))
			return (stop_simu(philo, NULL), NULL);
		if (take_forks(philo))
			return (stop_simu(philo, NULL), NULL);
		if (update_time(philo))
			return (stop_simu(philo, NULL), NULL);
		if (print_message("is eating", philo, 0))
			return (stop_simu(philo, NULL), NULL);
		ft_usleep(philo->time_data.time_to_eat);
		if (drop_forks(philo))
			return (stop_simu(philo, NULL), NULL);
		if (!philo->time_data.nb_meal)
			break ;
		if (print_message("is sleeping", philo, 0))
			return (stop_simu(philo, NULL), NULL);
		ft_usleep(philo->time_data.time_to_sleep);
	}
	return (end_of_loop(philo));
}
