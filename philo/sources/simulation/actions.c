/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:20:21 by florian           #+#    #+#             */
/*   Updated: 2024/07/17 13:43:28 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool    fork_is_free(t_philo *philo, pthread_mutex_t *fork_mtx, bool *fork)
{
    long int    time;

    time = get_time();
    if (time < 0)
        return (1);
    while (!check_death(philo))
    {
        if (pthread_mutex_lock(fork_mtx))
            break ;
        if (*fork)
        {
            if (pthread_mutex_unlock(fork_mtx))
                break ;
            return (0);
        }
        if (pthread_mutex_unlock(fork_mtx))
            break ;
        if (update_time(philo, time))
            break;
        time = get_time();
        if (time < 0)
            return (1);
    }
    return (1);
}

bool  take_forks(t_philo *philo)
{
    if (fork_is_free(philo, philo->shared_mtx.right_fork, &philo->right_fork))
        return (1);

    // take right fork
    if (pthread_mutex_lock(philo->shared_mtx.right_fork))
        return (ft_perror("error -> lock mutex\n"), 1); 
    philo->right_fork = 0;
    if (pthread_mutex_unlock(philo->shared_mtx.right_fork))
        return (ft_perror("error -> unlock mutex\n"), 1);
    if (print_message(philo, 0))
        return (1);

    if (fork_is_free(philo, philo->shared_mtx.left_fork, philo->left_fork))
        return (1);
    
    // take left fork
    if (pthread_mutex_lock(philo->shared_mtx.left_fork))
        return (ft_perror("error -> lock mutex\n"), 1);
    *(philo->left_fork) = 0;
    if (pthread_mutex_unlock(philo->shared_mtx.left_fork))
        return (ft_perror("error -> unlock mutex\n"), 1);
    return (print_message(philo, 0));
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

bool  think_act(void *arg)
{
    t_philo         *philo;

    philo = (t_philo *) arg;
    if (print_message(philo, 3))
        return (1);
    return (take_forks(philo));
}

bool  eat_act(t_philo *philo)
{
    long int        time;

    philo->time_data.time_to_die = philo->time_data.args[1];
    if (print_message(philo, 1))
        return (1);
    time = get_time();
    ft_usleep(philo->time_data.time_to_eat);
    if (update_time(philo, time))
        return (1);
    return (drop_forks(philo));
}

bool  sleep_act(t_philo *philo)
{
    long int  time;

    if (print_message(philo, 2))
        return (1);
    time = get_time();
    ft_usleep(philo->time_data.time_to_sleep);
    return (update_time(philo, time));
}
