/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:20:21 by florian           #+#    #+#             */
/*   Updated: 2024/07/17 19:45:43 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool    fork_is_free(t_philo *philo, pthread_mutex_t *fork_mtx, bool *fork)
{
    if (update_time(philo))
        return (1);
    if (philo->time_data.time_to_die <= 0)
        return (print_message(philo, 4), 1);
    while (!check_death(philo))
    {
        if (pthread_mutex_lock(fork_mtx))
            break ;
        if (*fork)
        {
            if (!pthread_mutex_unlock(fork_mtx))
                return (0);
            break;
        }
        if (pthread_mutex_unlock(fork_mtx))
            break ;
        if (update_time(philo))
            break;
        if (philo->time_data.time_to_die <= 0)
            return (print_message(philo, 4), 1);
    }
    return (1);
}

bool  take_forks(t_philo *philo)
{
    if (philo->index)
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
    else
    {
        if (fork_is_free(philo, philo->shared_mtx.left_fork, philo->left_fork))
            return (1);

        // take left fork
        if (pthread_mutex_lock(philo->shared_mtx.left_fork))
            return (ft_perror("error -> lock mutex\n"), 1);
        *(philo->left_fork) = 0;
        if (pthread_mutex_unlock(philo->shared_mtx.left_fork))
            return (ft_perror("error -> unlock mutex\n"), 1);
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

        return (print_message(philo, 0));

    }

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
    if (update_time(philo))
        return (1);
    if (philo->time_data.time_to_die <= 0)
        return (print_message(philo, 4));
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
    philo->time_data.time_to_die = philo->time_data.death_time;
    if (update_time(philo))
        return (1);
    if (philo->time_data.time_to_die <= 0)
        return (print_message(philo, 4));
    if (print_message(philo, 1))
        return (1);
    ft_usleep(philo->time_data.time_to_eat);
    if (update_time(philo))
        return (1);
    if (philo->time_data.time_to_die <= 0)
        return (print_message(philo, 4));
    return (drop_forks(philo));
}

bool  sleep_act(t_philo *philo)
{
    if (update_time(philo))
        return (1);
    if (philo->time_data.time_to_die <= 0)
        return (print_message(philo, 4));
    if (print_message(philo, 2))
        return (1);
    // if (update_time(philo))
    //     return (1);
    ft_usleep(philo->time_data.time_to_sleep);
    if (update_time(philo))
        return (1);
    if (philo->time_data.time_to_die <= 0)
        return (print_message(philo, 4));
    return (0);
}
