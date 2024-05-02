/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:17:50 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/02 18:45:46 by fberthou         ###   ########.fr       */
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

	int				      *args;
  int             time_to_die;
  int             time_to_eat;
  int             time_to_sleep;
  int             nb_lunch;
  size_t          index;
  bool            *ready;
  pthread_mutex_t shared_mutex[1];


  struct s_fork   *fork_ptr;
	struct s_philo	*head_lst;
	struct s_philo	*next;
}	t_philo ;

#endif
