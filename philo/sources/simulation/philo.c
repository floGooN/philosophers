/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:21:00 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/24 20:23:14 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int print_death(t_philo *philo);

static inline long int  get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long int)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

static inline int	print_message(char *msg, t_philo *philo)
{
	pthread_mutex_lock(philo->shared_mtx.print_mtx);
	if (*(philo->shared_res.stop_simu) == 1)
	{
		pthread_mutex_unlock(philo->shared_mtx.print_mtx);
		return (1);
	}
	printf("%ld %d %s\n", get_time() - philo->time_data.start_time,
		philo->index, msg);
	pthread_mutex_unlock(philo->shared_mtx.print_mtx);
	return (0);
}

static inline int   take_right(t_philo *philo)
{
    while (1)
    {
        pthread_mutex_lock(philo->shared_mtx.r_fork_mtx);
        if (philo->shared_res.right_fork == 1)
        {
            philo->shared_res.right_fork = 0;
            pthread_mutex_unlock(philo->shared_mtx.r_fork_mtx);
            break ;
        }
        pthread_mutex_unlock(philo->shared_mtx.r_fork_mtx);
		if (get_time()
			- philo->time_data.last_time >= philo->time_data.time_to_die)
			return (print_death(philo));
		usleep(10 * philo->nb_philo);
    }
    return (print_message("has taken a fork", philo));
}

static inline int   take_forks(t_philo *philo)
{
    if (take_right(philo))
        return (1);
    while (1)
    {
        pthread_mutex_lock(philo->shared_mtx.l_fork_mtx);
        if (*(philo->shared_res.left_fork) == 1)
        {
            *(philo->shared_res.left_fork) = 0;
            pthread_mutex_unlock(philo->shared_mtx.l_fork_mtx);
            break ;
        }
        pthread_mutex_unlock(philo->shared_mtx.l_fork_mtx);
		if (get_time()
			- philo->time_data.last_time >= philo->time_data.time_to_die)
			return (print_death(philo));
		usleep(10 * philo->nb_philo);
    }
    if (print_message("has taken a fork", philo))
        return (1);
    return (update_time(philo));
}
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_everybody_pls(philo);
	while (philo->time_data.nb_meal)
	{
		if (print_message("is thinking", philo))
            break ;
        if (take_forks(philo))
            break ;
		if (print_message("is eating", philo))
            break ;
		ft_usleep(philo->time_data.time_to_eat);
		drop_forks(philo);
		if (!philo->time_data.nb_meal)
		{
            print_message("is sleeping", philo);
			break ;
        }
		if (print_message("is sleeping", philo))
            break ;
		ft_usleep(philo->time_data.time_to_sleep);
	}
	return (end_of_loop(philo));
}
