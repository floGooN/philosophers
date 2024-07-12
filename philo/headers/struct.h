/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:17:50 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/12 11:08:08 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>

typedef struct s_main_th
{
  bool            ready;
  bool            is_dead;
  pthread_mutex_t ready_mutex;
  pthread_mutex_t isdead_mutex;
} t_main_th;

typedef struct s_data
{
	int       *args;
  long int  start_time;
  long int  time_to_die;
  long int  time_to_eat;
  long int  time_to_sleep;
  int       nb_meal;
} t_data;

typedef struct s_philo
{
	pthread_t		    philo_id;
  int             index;
  
  t_data          time_data;

  pthread_mutex_t *print_mutex;
  pthread_mutex_t *ready_mutex;
  pthread_mutex_t *isdead_mutex;

  pthread_mutex_t fork_mutex;
  bool            fork;

  pthread_mutex_t *left_fork;

  bool            *ready;
  bool            *is_dead;

}	t_philo ;

#endif
