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

#ifndef INIT_H
# define INIT_H

# include <stdlib.h>

# define MUTEX_ERROR "Error -> init mutex\n"
# define LST_ERROR   "Error -> init list\n"

void	*ft_calloc(size_t nmemb, size_t size);
void  free_lst(t_philo *head_lst);
int		print_error(char *str);

#endif
