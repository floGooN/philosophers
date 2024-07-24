/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:17:50 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/24 19:55:43 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <pthread.h>
# include <stdbool.h>
# include <stdatomic.h>

typedef struct s_time
{
	long int		start_time;
	long int		last_time;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				nb_meal;
}   t_time;

typedef struct s_shared_mtx
{
	pthread_mutex_t	*ready_mtx;
	pthread_mutex_t	*end_mtx;
	pthread_mutex_t	*print_mtx;
	pthread_mutex_t	*r_fork_mtx;
	pthread_mutex_t	*l_fork_mtx;
}   t_shared_mtx;

typedef struct  s_shared_resources
{
	bool		right_fork;
	bool		*left_fork;
	atomic_int  *stop_simu;
	atomic_int	*counter;
}   t_shared_res ;

typedef struct s_philo
{
	pthread_t		philo_id;
	int				index;
	int				nb_philo;
    t_time			time_data;
	t_shared_mtx	shared_mtx;
    t_shared_res    shared_res;
}   t_philo;

typedef struct s_main_th
{
	t_philo			*philo_tab;
	atomic_int      stop_simu;
	atomic_int  	counter;
	pthread_mutex_t	ready_mutex;
	pthread_mutex_t	end_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*all_forks_mtx;
}   t_main_th;

#endif
