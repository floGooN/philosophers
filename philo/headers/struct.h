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
  pthread_mutex_t mutex;
  bool            fork;
} t_fork ;

typedef struct s_philo
{
	pthread_t		    philo_id;
	int				      *args;
  struct s_fork   *fork_ptr;
	struct s_philo	*next;
}	t_philo ;


#endif
