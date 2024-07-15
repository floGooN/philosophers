/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:17:50 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/09 17:57:34 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>

typedef struct s_main_th
{
    int               tab_arg[5];
    pthread_mutex_t   ready_mutex;
    pthread_mutex_t   isdead_mutex;
    bool              is_dead;
    bool              ready;
}   t_main_th;

typedef struct s_philo
{
	pthread_t       philo_id;
    int             index;
    time_t          start_time;

    pthread_mutex_t *print_mutex;
    pthread_mutex_t *ready_mutex;
    pthread_mutex_t *isdead_mutex;

    pthread_mutex_t fork_mutex;
    bool            fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;

    long int        time_to_die;
    long int        time_to_eat;
    long int        time_to_sleep;
    int             nb_meal;
    bool            *ready;
    bool            *is_dead;

	int		        *args;
}	t_philo ;

#endif
