/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:20:21 by florian           #+#    #+#             */
/*   Updated: 2024/07/18 13:15:36 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool  take_forks(t_philo *philo)
{
    // take right fork
    while (1)
    {
        if (pthread_mutex_lock(philo->shared_mtx.right_fork))
            return (ft_perror("error -> lock mutex\n"), 1);
        if (!philo->right_fork)
        {
            if (pthread_mutex_unlock(philo->shared_mtx.right_fork))
                return (ft_perror("error -> unlock mutex\n"), 1);
        }
        else
        {
            philo->right_fork = 0;
            if (pthread_mutex_unlock(philo->shared_mtx.right_fork))
                return (ft_perror("error -> unlock mutex\n"), 1);
            if (print_message("has taken a fork", philo, 0))
                return (1);
            break ;
        }
        if (check_death(philo))
            return (1);
        usleep(100);
    }
    // take left fork
    while (1)
    {
        if (pthread_mutex_lock(philo->shared_mtx.left_fork))
            return (ft_perror("error -> lock mutex\n"), 1);
        if (!*(philo->left_fork))
        {
            if (pthread_mutex_unlock(philo->shared_mtx.left_fork))
                return (ft_perror("error -> unlock mutex\n"), 1);
        }
        else
        {
            *(philo->left_fork) = 0;
            if (pthread_mutex_unlock(philo->shared_mtx.left_fork))
                return (ft_perror("error -> unlock mutex\n"), 1);
            return (print_message("has taken a fork", philo, 0));
        }
        if (check_death(philo))
            return (1);
        usleep(100);
    }
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

// bool  think_act(t_philo *philo)
// {
    
// }

// bool  eat_act(t_philo *philo)
// {
//     long int    ret_value;

//     ret_value = update_time(philo);
//     if (ret_value)
//     {
//         if (ret_value == -1)
//             return (1);
//         else if (print_message(philo, 4))
//             return (1);
//     }
//     if (print_message(philo, 1))
//         return (1);
//     ft_usleep(philo->time_data.time_to_eat);
//     return (drop_forks(philo));
// }

// bool  sleep_act(t_philo *philo)
// {
//     // long int    ret_value;
    
//     // ret_value = update_time(philo);
//     // if (ret_value == -1)
//     //     return (1);
//     // if (ret_value == 1)
//     // {
//     //     if (print_message(philo, 4))
//     //         return (1);
//     // }
    
//     return (0);
// }
