/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:21:00 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/22 13:34:17 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void		*end_of_loop(t_philo *philo);
void		wait_everybody_pls(t_philo *philo);
void		drop_forks(t_philo *philo);

static bool	check_status(t_philo *philo)
{
	pthread_mutex_lock(philo->shared_mtx.stop_mtx);
	if (*(philo->stop_simu))
	{
		pthread_mutex_unlock(philo->shared_mtx.stop_mtx);
		return (1);
	}
	pthread_mutex_unlock(philo->shared_mtx.stop_mtx);
	return (0);
}

static void	print_message(char *msg, t_philo *philo)
{
	pthread_mutex_lock(philo->shared_mtx.print_mtx);
	if (check_status(philo))
	{
		pthread_mutex_unlock(philo->shared_mtx.print_mtx);
		return ;
	}
	printf("%ld %d %s\n", get_time() - philo->time_data.start_time,
		philo->index, msg);
	pthread_mutex_unlock(philo->shared_mtx.print_mtx);
	return ;
}

static int	take_right(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->shared_mtx.right_fork);
		if (philo->right_fork)
		{
			philo->right_fork = 0;
			pthread_mutex_unlock(philo->shared_mtx.right_fork);
			pthread_mutex_lock(philo->shared_mtx.print_mtx);
			if (check_status(philo))
				return (pthread_mutex_unlock(philo->shared_mtx.print_mtx), 1);
			printf("%ld %d has taken a fork\n", get_time()
				- philo->time_data.start_time, philo->index);
			return (pthread_mutex_unlock(philo->shared_mtx.print_mtx));
		}
		pthread_mutex_unlock(philo->shared_mtx.right_fork);
		if (get_time()
			- philo->time_data.last_time >= philo->time_data.time_to_die)
			return (1);
		usleep(100);
	}
	return (1);
}

static void	take_forks(t_philo *philo)
{
	if (take_right(philo))
		return ;
	while (1)
	{
		pthread_mutex_lock(philo->shared_mtx.left_fork);
		if (*(philo->left_fork))
		{
			*(philo->left_fork) = 0;
			pthread_mutex_unlock(philo->shared_mtx.left_fork);
			pthread_mutex_lock(philo->shared_mtx.print_mtx);
			if (check_status(philo))
				break ;
			printf("%ld %d has taken a fork\n", get_time()
				- philo->time_data.start_time, philo->index);
			break ;
		}
		pthread_mutex_unlock(philo->shared_mtx.left_fork);
		if (get_time()
			- philo->time_data.last_time >= philo->time_data.time_to_die)
			return ;
		usleep(100);
	}
	pthread_mutex_unlock(philo->shared_mtx.print_mtx);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_everybody_pls(philo);
	while (philo->time_data.nb_meal)
	{
		print_message("is thinking", philo);
		take_forks(philo);
		if (update_time(philo))
			return (NULL);
		print_message("is eating", philo);
		ft_usleep(philo->time_data.time_to_eat);
		drop_forks(philo);
		if (!philo->time_data.nb_meal)
		{
			pthread_mutex_lock(philo->shared_mtx.print_mtx);
			printf("%ld %d is thinking\n", get_time()
				- philo->time_data.start_time, philo->index);
			pthread_mutex_unlock(philo->shared_mtx.print_mtx);
			break ;
		}
		print_message("is sleeping", philo);
		ft_usleep(philo->time_data.time_to_sleep);
	}
	return (end_of_loop(philo));
}
