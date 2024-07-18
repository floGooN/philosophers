/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:20:21 by florian           #+#    #+#             */
/*   Updated: 2024/07/18 17:58:57 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static bool take_a_fork(t_philo *philo, pthread_mutex_t *fork_mtx, bool *fork)
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
        if (check_death(philo))
            return (1);
        usleep(100);
    }
    return (0);
}

bool  take_forks(t_philo *philo)
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

bool  drop_forks(t_philo *philo)
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
    return (0);
}

bool  eat_act(t_philo *philo)
{
    long int    ret_value;

    ret_value = update_time(philo);
    if (ret_value)
    {
        if (ret_value == -1)
            return (stop_simu(philo, NULL), 1);
        else
        {
            if (print_message("died", philo, 1))
                return (stop_simu(philo, NULL), 1);
        }
    }
    if (print_message("is eating", philo, 0))
        return (stop_simu(philo, NULL), 1);
    ft_usleep(philo->time_data.time_to_eat);
    if (drop_forks(philo))
        return (1);
    ret_value = update_time(philo);
    if (ret_value)
    {
        if (ret_value == -1)
            return (stop_simu(philo, NULL), 1);
        else
        {
            if (print_message("died", philo, 1))
                return (stop_simu(philo, NULL), 1);
        }
    }
    return (0);
}
