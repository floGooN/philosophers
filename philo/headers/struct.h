/*
    HEADER 42
    HEADER 42
    HEADER 42
    HEADER 42
    HEADER 42
    HEADER 42
    HEADER 42
    HEADER 42
    HEADER 42
*/


#ifndef STRUCT_H
# define STRUCT_H

#include <pthread.h>
#include <stdbool.h>

typedef struct  s_fork
{
  pthread_mutex_t fork_mutex;
  bool            fork;
} t_fork ;

typedef struct s_philo
{
	pthread_t		    philo_id;
	int				      *args;
  pthread_mutex_t shared_mutex[2];
  struct s_fork   *fork_ptr;
	struct s_philo	*next;
	struct s_philo	*head_lst;
  int             index;
}	t_philo ;


#endif
