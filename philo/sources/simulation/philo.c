/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:21:00 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/25 23:59:02 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static inline long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long int)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

static inline void	print_message(char *msg, t_philo *philo)
{
	pthread_mutex_lock(philo->shared_mtx.print_mtx);
	if (*(philo->shared_res.stop_simu) == 1)
	{
		pthread_mutex_unlock(philo->shared_mtx.print_mtx);
		return ;
	}
	printf("%ld %d %s\n", get_time() - philo->time_data.start_time, \
		philo->index, msg);
	pthread_mutex_unlock(philo->shared_mtx.print_mtx);
	return ;
}

static inline void	take_right(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->shared_mtx.r_fork_mtx);
		if (get_time() \
			- philo->time_data.last_time >= philo->time_data.time_to_die)
		{
			*(philo->shared_res.stop_simu) = 1;
			pthread_mutex_unlock(philo->shared_mtx.r_fork_mtx);
			return ;
		}
		if (philo->shared_res.right_fork == 1)
		{
			philo->shared_res.right_fork = 0;
			pthread_mutex_unlock(philo->shared_mtx.r_fork_mtx);
			return (print_message("has taken a fork", philo));
		}
		pthread_mutex_unlock(philo->shared_mtx.r_fork_mtx);
		usleep(10 * philo->nb_philo);
	}
}

static inline void	take_forks(t_philo *philo)
{
	take_right(philo);
	while (1)
	{
		pthread_mutex_lock(philo->shared_mtx.l_fork_mtx);
		if (get_time() - philo->time_data.last_time >= \
			philo->time_data.time_to_die)
		{
			*(philo->shared_res.stop_simu) = 1;
			pthread_mutex_unlock(philo->shared_mtx.l_fork_mtx);
			return ;
		}
		if (*(philo->shared_res.left_fork) == 1)
		{
			*(philo->shared_res.left_fork) = 0;
			pthread_mutex_unlock(philo->shared_mtx.l_fork_mtx);
			return (print_message("has taken a fork", philo));
		}
		pthread_mutex_unlock(philo->shared_mtx.l_fork_mtx);
		usleep(10 * philo->nb_philo);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_everybody_pls(philo);
	while (1)
	{
		print_message("is thinking", philo);
		take_forks(philo);
		update_time(philo);
		print_message("is eating", philo);
		ft_usleep(philo->time_data.time_to_eat, philo->shared_res.stop_simu);
		drop_forks(philo);
		if (*(philo->shared_res.stop_simu) == 1 || \
			philo->time_data.nb_meal == 0 || \
			philo->time_data.nb_meal == -2)
		{
			if (philo->time_data.nb_meal == 0)
				end_of_loop(philo);
			print_message("is sleeping", philo);
			break ;
		}
		print_message("is sleeping", philo);
		ft_usleep(philo->time_data.time_to_sleep, philo->shared_res.stop_simu);
	}
	return (end_of_simu(philo));
}
