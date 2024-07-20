/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:21:00 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/20 11:03:56 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	*end_of_loop(t_philo *philo)
{
	if (pthread_mutex_lock(philo->shared_mtx.counter_mtx))
		return (NULL);
	*(philo->monitor_counter) -= 1;
	if (pthread_mutex_unlock(philo->shared_mtx.counter_mtx))
		return (NULL);
	return (NULL);
}

static void	ft_usleep(long int time)
{
	const long int	start = get_time();

	while ((get_time() - start) < time)
		usleep(time / 10);
}

static int	wait_loop(t_philo *philo)
{
	while (!check_death(philo))
	{
		if (pthread_mutex_lock(philo->shared_mtx.ready_mtx))
			return (ft_perror("error -> lock mtx (wait_loop)\n"), 1);
		if (*(philo->ready))
		{
			if (pthread_mutex_unlock(philo->shared_mtx.ready_mtx))
				return (ft_perror("error -> unlock mtx (wait_loop)\n"), 1);
			return (0);
		}
		if (pthread_mutex_unlock(philo->shared_mtx.ready_mtx))
			return (ft_perror("error -> unlock mtx (wait_loop)\n"), 1);
		if (pthread_mutex_lock(philo->shared_mtx.isdead_mtx))
			return (ft_perror("error -> unlock mtx (wait_loop)\n"), 1);
		if (*(philo->is_dead))
			return (pthread_mutex_unlock(philo->shared_mtx.isdead_mtx), 1);
		if (pthread_mutex_unlock(philo->shared_mtx.isdead_mtx))
			return (ft_perror("error -> unlock mtx (wait_loop)\n"), 1);
		usleep(100);
	}
	return (1);
}

static int	init_routine(t_philo *philo)
{
	if (wait_loop(philo))
		return (1);
	if (philo->index % 2)
		usleep(500);
	philo->time_data.start_time = get_time();
	philo->time_data.last_time = philo->time_data.start_time;
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (init_routine(philo))
		return (stop_simu(philo, NULL), NULL);
	while (philo->time_data.nb_meal)
	{
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
		if (print_message("is thinking", philo, 0))
			return (stop_simu(philo, NULL), NULL);
	}
	return (end_of_loop(philo));
}
