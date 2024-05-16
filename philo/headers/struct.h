/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:17:50 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/16 19:07:38 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>

typedef struct s_philo
{
	pthread_t		    philo_id;
  long int        start_time;

  pthread_mutex_t *print_mutex;
  pthread_mutex_t *ready_mutex;
  pthread_mutex_t *isdead_mutex;

  pthread_mutex_t fork_mutex;
  bool            fork;

  pthread_mutex_t *right_fork;
  pthread_mutex_t *left_fork;

  int             index;
  long int        time_to_die;
  long int        time_to_eat;
  long int        time_to_sleep;
  int             nb_meal;
  bool            *ready;
  bool            *is_dead;

	int				      *args;
}	t_philo ;

#endif
