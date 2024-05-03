/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:17:50 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/03 21:47:27 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>

typedef struct  s_fork
{
  pthread_mutex_t fork_mutex[2];
  bool            fork;
} t_fork ;

typedef struct s_philo
{
	pthread_t		    philo_id;
  struct timeval  philo_tv;

  size_t          index;
  int             time_to_die;
  int             time_to_eat;
  int             time_to_sleep;
  int             nb_meal;
  bool            *ready;
  pthread_mutex_t *print_mutex;

  // following ptr -> malloc in init
	int				      *args;
  struct s_fork   *fork_ptr;

}	t_philo ;

#endif
