/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:17:50 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/04 12:19:12 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>

// typedef struct s_checker
// {
//   pthread_t th_id;
//   bool      *ready_ptr;
//   void      **ret_value;
// } t_check ;

typedef struct  s_fork
{
  pthread_mutex_t fork_mutex[2];
  bool            fork;
} t_fork ;

typedef struct s_philo
{
	pthread_t		    philo_id;
  struct timeval  philo_tv;

  pthread_mutex_t *print_mutex;
  pthread_mutex_t *ready_mutex;
  pthread_mutex_t *retval_mutex;
  int             index;
  int             time_to_die;
  int             time_to_eat;
  int             time_to_sleep;
  int             nb_meal;
  bool            *ready;
  void            **ret_value;

  // following ptr -> malloc in init
	int				      *args;
  struct s_fork   *fork_ptr;

}	t_philo ;

#endif
