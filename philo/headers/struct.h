/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:17:50 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/24 16:23:59 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <pthread.h>
# include <stdbool.h>

typedef struct s_time
{
	long int		start_time;
	long int		last_time;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				nb_meal;
}					t_time;

typedef struct s_shared_mtx
{
	pthread_mutex_t	*ready_mtx;
	pthread_mutex_t	*end_mtx;
	pthread_mutex_t	*print_mtx;
	pthread_mutex_t	*counter_mtx;
	pthread_mutex_t	*stop_mtx;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}					t_shared_mtx;

typedef struct s_philo
{
	pthread_t		philo_id;
	int				index;
	int				*counter;
	int				nb_philo;
	int 			*stop_simu;
	bool			right_fork;
	bool			*left_fork;
	t_time			time_data;
	t_shared_mtx	shared_mtx;
}					t_philo;

typedef struct s_main_th
{
	t_philo			*philo_tab;
	int 			*stop_simu;
	int				counter;
	pthread_mutex_t	ready_mutex;
	pthread_mutex_t	end_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	counter_mtx;
	pthread_mutex_t	*stop_mtx;
	pthread_mutex_t	*all_forks;
}					t_main_th;

#endif
