/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:21:00 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/21 13:38:40 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	*end_of_loop(t_philo *philo)
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

static void	wait_everybody_pls(t_philo *philo)
{
    pthread_mutex_lock(philo->shared_mtx.ready_mtx);
    pthread_mutex_unlock(philo->shared_mtx.ready_mtx);
    if (philo->index % 2)
        usleep(20 * philo->nb_philo);
    philo->time_data.start_time = get_time();
    philo->time_data.last_time = philo->time_data.start_time;
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_everybody_pls(philo);
	while (philo->time_data.nb_meal)
	{
		if (print_message("is thinking", philo))
			return (NULL);
	
	
		if (take_forks(philo))
			return (NULL);
	
		if (update_time(philo))
			return (NULL);	
	
		if (print_message("is eating", philo))
			return (NULL);
		ft_usleep(philo->time_data.time_to_eat);
		if (drop_forks(philo))
			return (NULL);
	
		if (!philo->time_data.nb_meal)
			break ;
	
	
		if (print_message("is sleeping", philo))
			return (NULL);
		ft_usleep(philo->time_data.time_to_sleep);
	}
	return (end_of_loop(philo));
}
