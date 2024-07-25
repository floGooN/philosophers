/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:20:21 by florian           #+#    #+#             */
/*   Updated: 2024/07/25 19:32:27 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static inline long int  get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long int)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	update_time(t_philo *philo)
{
	const long int	curr_time = get_time();

	if (curr_time - philo->time_data.last_time >= philo->time_data.time_to_die)
        *(philo->shared_res.stop_simu) = 1;
    else
	    philo->time_data.last_time = curr_time;
}

void	drop_forks(t_philo *philo)
{
    pthread_mutex_lock(philo->shared_mtx.r_fork_mtx);
	philo->shared_res.right_fork = 1;
    pthread_mutex_unlock(philo->shared_mtx.r_fork_mtx);
    pthread_mutex_lock(philo->shared_mtx.l_fork_mtx);
	*(philo->shared_res.left_fork) = 1;
    pthread_mutex_unlock(philo->shared_mtx.l_fork_mtx);
    if (philo->time_data.nb_meal > 0)
        philo->time_data.nb_meal--;
	return ;
}

void	ft_usleep(long int time, atomic_int *stop)
{
	const long int	start = get_time();

	while ((get_time() - start) < time)
    {
        if (!*(stop))
		    usleep(time / 10);
        else
            return ;
    }
}

void    letal_loop(t_philo *philo)
{
    // decrement philo->counter
    *(philo->shared_res.counter) -= 1;
    // if last philo
    if (*(philo->shared_res.counter) == 0)
    {
        if (*(philo->shared_res.stop_simu) == 0) // si personne n'est mort
        { // stop and exit loop counter -2 == reussite
            *(philo->shared_res.stop_simu) = 1;
            *(philo->shared_res.counter) = -2;
        }
        return ;
    }
    else // else continue the loop
        philo->time_data.nb_meal = -1;
    while (1)
    {

		print_message("is sleeping", philo);
		ft_usleep(philo->time_data.time_to_sleep, philo->shared_res.stop_simu);

    }

    if (*(philo->shared_res.stop_simu))
        return ;
}
