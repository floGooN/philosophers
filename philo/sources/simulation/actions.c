/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:20:21 by florian           #+#    #+#             */
/*   Updated: 2024/07/16 14:03:50 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool  take_forks(t_philo *philo)
{
    if (philo->index % 2)
    {
        // take right fork
        if (pthread_mutex_lock(philo->shared_mtx.right_fork))
            return (1); // error taking mutex
        if (check_death(philo))
            return (pthread_mutex_unlock(philo->shared_mtx.right_fork), 1);
        philo->right_fork = 0;
        if (print_message(philo, 0))
            return (pthread_mutex_unlock(philo->shared_mtx.right_fork), 1);
        
        
        // take left fork
        if (pthread_mutex_lock(philo->shared_mtx.left_fork))
            return (pthread_mutex_unlock(philo->shared_mtx.right_fork), 1); // error taking mutex
        if (check_death(philo))
            return (pthread_mutex_unlock(philo->shared_mtx.right_fork), 1);
        *(philo->left_fork) = 0;
        if (print_message(philo, 0))
            return (pthread_mutex_unlock(philo->shared_mtx.right_fork), \
                    pthread_mutex_unlock(philo->shared_mtx.left_fork), 1);
    }
    else
    {
        
        // take right fork
        if (pthread_mutex_lock(philo->shared_mtx.right_fork))
            return (pthread_mutex_unlock(philo->shared_mtx.left_fork), 1); // error taking mutex
        if (check_death(philo))
            return (pthread_mutex_unlock(philo->shared_mtx.right_fork), 1);
        philo->right_fork = 0;
        if (print_message(philo, 0))
            return (pthread_mutex_unlock(philo->shared_mtx.left_fork), \
                    pthread_mutex_unlock(philo->shared_mtx.right_fork), 1);
        // take left fork
        if (pthread_mutex_lock(philo->shared_mtx.left_fork))
            return (1); // error taking mutex
        if (check_death(philo))
            return (pthread_mutex_unlock(philo->shared_mtx.right_fork), 1);
        *(philo->left_fork) = 0;
        if (print_message(philo, 0))
            return (pthread_mutex_unlock(philo->shared_mtx.left_fork), 1);
    }
    return (0);
}

bool  drop_forks(t_philo *philo)
{
    philo->right_fork = 1;
    *(philo->left_fork) = 1;
    if (pthread_mutex_unlock(philo->shared_mtx.right_fork) || \
        pthread_mutex_unlock(philo->shared_mtx.left_fork))
        return (1);
    return (0);
}

bool  think_act(void *arg)
{
    t_philo         *philo;

    philo = (t_philo *) arg;
    print_message(philo, 3);
    return (take_forks(philo));
}

bool  eat_act(t_philo *philo)
{
    long int        time1;
    long int        time2;

    philo->time_data.time_to_die = philo->time_data.args[1];
    philo->time_data.time_to_eat = philo->time_data.args[2];
    if (print_message(philo, 1))
        return (1);
    time1 = get_time();
    ft_usleep(philo->time_data.time_to_eat);
    time2 = get_time();
    philo->time_data.time_to_die -= time2 - time1;
    philo->time_data.time_to_eat -= time2 - time1;
    if (philo->time_data.time_to_die <= 0)
        return (print_message(philo, 4));
    return (drop_forks(philo));
}

bool  sleep_act(t_philo *philo)
{
    long int  time1;
    long int  time2;

    philo->time_data.time_to_sleep = philo->time_data.args[3];
    if (print_message(philo, 2))
        return (1);
    time1 = get_time();
    ft_usleep(philo->time_data.time_to_sleep);
    time2 = get_time();
    
    philo->time_data.time_to_die -= time2 - time1;
    philo->time_data.time_to_sleep -= time2 - time1;
    if (philo->time_data.time_to_die <= 0)
        return (print_message(philo, 4));
    return (0);
}
