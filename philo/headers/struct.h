/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:17:50 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/20 20:27:28 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <pthread.h>
# include <stdbool.h>

typedef struct s_time
{
	long int		start_time;
	long int		death_time;
	long int		last_time;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				nb_meal;
}					t_time;

typedef struct s_shared_mtx
{
	pthread_mutex_t	*print_mtx;
	pthread_mutex_t	*ready_mtx;
	pthread_mutex_t	*isdead_mtx;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*counter_mtx;
}					t_shared_mtx;

typedef struct s_philo
{
	pthread_t		philo_id;
	int				index;
	int				*monitor_counter;
    int             nb_philo;
	bool			*is_dead;
	bool			right_fork;
	bool			*left_fork;
	t_time			time_data;
	t_shared_mtx	shared_mtx;
}					t_philo;

typedef struct s_main_th
{
	bool			is_dead;
	int				counter;
	pthread_mutex_t	counter_mtx;
	pthread_mutex_t	ready_mutex;
	pthread_mutex_t	isdead_mutex;
	pthread_mutex_t	*all_forks;
}					t_main_th;

#endif
