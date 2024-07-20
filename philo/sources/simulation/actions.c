/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:20:21 by florian           #+#    #+#             */
/*   Updated: 2024/07/20 11:03:52 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	print_message(char *msg, t_philo *philo, bool is_dead)
{
	if (pthread_mutex_lock(philo->shared_mtx.print_mtx))
		return (ft_perror("error -> lock mtx (print_message)\n"), 1);
	if (check_death(philo))
		return (pthread_mutex_unlock(philo->shared_mtx.print_mtx), 1);
	printf("%ld %d %s\n", get_time() - philo->time_data.start_time,
		philo->index, msg);
	if (is_dead)
	{
		change_death_status(philo);
		pthread_mutex_unlock(philo->shared_mtx.print_mtx);
		return (1);
	}
	if (pthread_mutex_unlock(philo->shared_mtx.print_mtx))
		return (ft_perror("error -> unlock mtx (print_message)\n"), 1);
	return (0);
}

static bool	take_a_fork(t_philo *philo, pthread_mutex_t *fork_mtx, bool *fork)
{
	while (1)
	{
		if (pthread_mutex_lock(fork_mtx))
			return (ft_perror("error -> lock mutex\n"), 1);
		if (!*fork)
		{
			if (pthread_mutex_unlock(fork_mtx))
				return (ft_perror("error -> unlock mutex\n"), 1);
		}
		else
		{
			*fork = 0;
			if (pthread_mutex_unlock(fork_mtx))
				return (ft_perror("error -> unlock mutex\n"), 1);
			break ;
		}
		if (get_time()
			- philo->time_data.last_time >= philo->time_data.death_time)
			return (print_message("died", philo, 1), 1);
		if (check_death(philo))
			return (1);
		usleep(100);
	}
	return (0);
}

bool	take_forks(t_philo *philo)
{
	if (take_a_fork(philo, philo->shared_mtx.right_fork, &(philo->right_fork)))
		return (1);
	if (print_message("has taken a fork", philo, 0))
		return (1);
	if (take_a_fork(philo, philo->shared_mtx.left_fork, philo->left_fork))
		return (1);
	if (print_message("has taken a fork", philo, 0))
		return (1);
	return (0);
}

bool	drop_forks(t_philo *philo)
{
	if (pthread_mutex_lock(philo->shared_mtx.right_fork))
		return (1);
	philo->right_fork = 1;
	if (pthread_mutex_unlock(philo->shared_mtx.right_fork))
		return (1);
	if (pthread_mutex_lock(philo->shared_mtx.left_fork))
		return (1);
	*(philo->left_fork) = 1;
	if (pthread_mutex_unlock(philo->shared_mtx.left_fork))
		return (1);
	if (philo->time_data.nb_meal > 0)
		(philo->time_data.nb_meal)--;
	return (0);
}
