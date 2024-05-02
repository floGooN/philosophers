/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:06:29 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/02 22:29:37 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>

#include <unistd.h>


/* ====	PROTOTYPES	==== */

// parsing/parsing.c
int		parsing(int argc, char **argv, int *tab_arg);

// main/utils.c
int		print_error(char *str);
void	*ft_calloc(size_t nmemb, size_t size);
void  free_lst(t_philo *head_lst);

// init/init.c
t_philo	*socrate_maker(int *tab_args);

/* ====	PROTOTYPES	==== */

/*void	*sleep_and_die(void *tab_arg)
{
	static pthread_t	new;
	struct timeval		tv[3];
	int					tmp;

	if (!new)
	{
		if (pthread_create(&new, NULL, sleep_and_die, tab_arg))
			return (NULL);
		return (&new);
	}
	write(1, "One fork for eating spaghetti!!\nShame on you, ", 46);
	write(1, "I prefer dying than eating !!\n", 31);
	gettimeofday(&tv[0], NULL);
	while (((int *)tab_arg)[1] > 0)
	{
		gettimeofday(&tv[1], NULL);
		usleep(30);
		gettimeofday(&tv[2], NULL);
  	((int *)tab_arg)[1] -= (int)((tv[2].tv_usec - tv[1].tv_usec));
	}
	gettimeofday(&tv[2], NULL);
	printf("%ld %ld died\n", ((tv[2].tv_usec - tv[0].tv_usec) * 1000 + \
                            (tv[2].tv_sec - tv[0].tv_sec) / 1000), new);
	return (NULL);
}*/

void  *print_message(pthread_mutex_t *mutex, long int time, \
                                size_t philo_num, int state)
{
  pthread_mutex_lock(mutex);
  if (state == 0)
    printf("%ld %zu has taken a fork\n", time, philo_num);
  else if (state == 1)
    printf("%ld %zu is eating\n", time, philo_num);
  else if (state == 2)
    printf("%ld %zu is sleeping\n", time, philo_num);
  else if (state == 3)
    printf("%ld %zu is thinkink\n", time, philo_num);
  else
    printf("%ld %ld died\n", time, philo_num);
  if (state <= 3)
  {
    pthread_mutex_unlock(mutex);
    return (NULL);
  }
  else
    return (mutex);
}

void  ft_usleep(int param)
{
  int i = 1;

  while (param > (5 * i))
  {
    usleep(5);
    i++;
  }
}

void  maj_time(struct timeval  *time_val, int *buffer, int *die)
{
  int tmp;

  tmp = (int) ((time_val[1].tv_usec - time_val[0].tv_usec) + \
              (time_val[1].tv_sec - time_val[0].tv_sec));
  *die -= tmp;
  *buffer -= tmp;
}

void *eat_routine(t_philo *lst)
{
  int             tmp;
  struct timeval  time_val[2];

  lst->time_to_die = lst->args[1];
	while (lst->time_to_eat > 0 && lst->time_to_die > 0)
	{
		gettimeofday(&time_val[0], NULL);
		ft_usleep(10);
		gettimeofday(&time_val[1], NULL);
    maj_time(time_val, &lst->time_to_eat, &lst->time_to_die);
	}
  pthread_mutex_lock(lst->print_mutex);
  printf("time to die = %d\n", lst->time_to_die);
  pthread_mutex_unlock(lst->print_mutex);
  if (lst->time_to_die <= 0)
    return (print_message(lst->print_mutex, lst->time_to_die, lst->index, 4));
  else
    return (print_message(lst->print_mutex, lst->time_to_die, lst->index, 1));
}


void *sleep_routine(t_philo *lst)
{
  int             tmp;
  struct timeval  time_val[2];

	while (lst->time_to_sleep > 0 && lst->time_to_die > 0)
	{
		gettimeofday(&time_val[0], NULL);
		ft_usleep(10);
		gettimeofday(&time_val[1], NULL);
    maj_time(time_val, &lst->time_to_sleep, &lst->time_to_die);
	}
  pthread_mutex_lock(lst->print_mutex);
  printf("time to die = %d\n", lst->time_to_die);
  pthread_mutex_unlock(lst->print_mutex);
  if (lst->time_to_die <= 0)
    return (print_message(lst->print_mutex, lst->time_to_die, lst->index, 4));
  else
    return (print_message(lst->print_mutex, lst->time_to_die, lst->index, 2));
}

// void *think_routine(void *arg)
// {
//   t_philo         *lst;
//   lst = (t_philo *) arg;
//   pthread_mutex_lock(&((t_philo *)arg)->shared_mutex[0]);
//   printf("thread nb %ld, index = %d from think\n", lst->index, lst->index);
//   pthread_mutex_unlock(&lst->shared_mutex[0]);
//   return (NULL);
// }

void  *routine_b(void *arg)
{
  t_philo *curr_philo;

  curr_philo = (t_philo *) arg;
  gettimeofday(&curr_philo->philo_tv, NULL);
  while (curr_philo->time_to_die)
  {
    if (curr_philo->time_to_die > 0)
      eat_routine(curr_philo);
    if (curr_philo->time_to_die > 0)
      sleep_routine(curr_philo);
  }
  pthread_mutex_lock(curr_philo->print_mutex);
  printf("ICI%d\n", curr_philo->index);
  pause();
  pthread_mutex_lock(curr_philo->print_mutex);

  return (NULL);
}

void  *routine_a(void *arg)
{
  t_philo *curr_philo;

  curr_philo = (t_philo *) arg;
  gettimeofday(&curr_philo->philo_tv, NULL);
  while (curr_philo->time_to_die)
  {
    if (curr_philo->time_to_die)
      sleep_routine(curr_philo);
    if (curr_philo->time_to_die)
      eat_routine(curr_philo);
  }
  pthread_mutex_lock(curr_philo->print_mutex);
  printf("ICI%d\n", curr_philo->index);
  pause();
  pthread_mutex_lock(curr_philo->print_mutex);
  return (NULL);
}

bool  launch_threads(t_philo *lst)
{
  while (lst)
  {
    if (lst->index % 2)
    {
      if (pthread_create(&(lst)->philo_id, NULL, routine_a, lst))
        return (1);
    }
    else
    {
      if (pthread_create(&(lst)->philo_id, NULL, routine_b, lst))
        return (1);
    }
    lst = lst->next;
  }
  return (0);
}

int	main(int argc, char **argv)
{
	int		  tab_arg[5];
	t_philo *head_lst;
  t_philo *tmp;

	if (argc != 5 && argc != 6)
		return (printf("Nb of arguments is invalid\n"), 0);
	if (parsing(argc, argv, tab_arg))
		return (0);
  if (argc == 5)
	{
    head_lst = socrate_maker(tab_arg);
		if (!head_lst)
        return (0);

    if (launch_threads(head_lst))
        return (free_lst(head_lst), 0);

    tmp = head_lst->next;
    while (tmp)
    {
      pthread_join(tmp->philo_id, NULL);
      tmp = tmp->next;
    }
    free_lst(head_lst);
	  return (0);
	}
}

	/*
	if (tab_arg[1] < tab_arg[2] || tab_arg[1] < tab_arg[3])
		// incoherent argument
	else
		// eat %d time and die
	*/
