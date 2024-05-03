/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:17:50 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/03 13:50:54 by fberthou         ###   ########.fr       */
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

  int             time_to_die;
  int             time_to_eat;
  int             time_to_sleep;
  int             nb_meal;
  size_t          index;
  struct timeval  philo_tv;

  // following ptr -> malloc in init
  pthread_mutex_t *print_mutex;
  struct s_fork   *fork_ptr;
	int				      *args;
  bool            *ready;

	struct s_philo	*head_lst;
	struct s_philo	*next;
}	t_philo ;

#endif
