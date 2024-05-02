/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:06:29 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/02 12:44:39 by florian          ###   ########.fr       */
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
                                long int philo_num, int state)
{
  pthread_mutex_lock(mutex);
  if (state == 0)
    printf("%ld %ld has taken a fork\n", time, philo_num);
  else if (state == 1)
    printf("%ld %ld is eating\n", time, philo_num);
  else if (state == 2)
    printf("%ld %ld is sleeping\n", time, philo_num);
  else if (state == 3)
    printf("%ld %ld is thinkink\n", time, philo_num);
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

void *eat_routine(void *arg)
{
  int     tmp;
  t_philo *lst;

  lst = (t_philo *) arg;
  while (*(lst->start_ptr))
    continue ;
  // gettimeofday(&lst->tv[0], NULL);
	while (lst->args[2] > 0 && lst->args[1] > 0)
	{
		gettimeofday(&lst->tv[0], NULL);
		usleep(10);
		gettimeofday(&lst->tv[1], NULL);
  	lst->args[2] -= (int) ((lst->tv[1].tv_usec - lst->tv[0].tv_usec) + \
              (lst->tv[1].tv_sec - lst->tv[0].tv_sec));
  	lst->args[1] -= (int) ((lst->tv[1].tv_usec - lst->tv[0].tv_usec) + \
              (lst->tv[1].tv_sec - lst->tv[0].tv_sec));
	}
	// gettimeofday(&lst->tv[1], NULL);
  // tmp = (int) (((lst->tv[1].tv_usec - lst->tv[0].tv_usec) + \
  //             (lst->tv[1].tv_sec - lst->tv[0].tv_sec)));
  // lst->args[1] -= tmp;
  if (lst->args[1] <= 0)
    return (print_message(&lst->shared_mutex[0], lst->args[1], lst->philo_id, 4));
  else
    return (print_message(&lst->shared_mutex[0], lst->args[1], lst->philo_id, 1));
}

void *sleep_routine(void *arg)
{
  int     tmp;
  t_philo *lst;

  lst = (t_philo *) arg;
  if (lst->index == 1)
    *(lst->start_ptr) = 0;
  while (*(lst->start_ptr))
    continue ;
  // gettimeofday(&lst->tv[0], NULL);
	while (lst->args[3] > 0)
	{
		gettimeofday(&lst->tv[0], NULL);
		usleep(10);
		gettimeofday(&lst->tv[1], NULL);
  	lst->args[3] -= (int) ((lst->tv[1].tv_usec - lst->tv[0].tv_usec) + \
              (lst->tv[1].tv_sec - lst->tv[0].tv_sec));
  	lst->args[1] -= (int) ((lst->tv[1].tv_usec - lst->tv[0].tv_usec) + \
              (lst->tv[1].tv_sec - lst->tv[0].tv_sec));
	}
	// gettimeofday(&lst->tv[1], NULL);
  // tmp = (((lst->tv[1].tv_usec - lst->tv[0].tv_usec) + \
  //             (lst->tv[1].tv_sec - lst->tv[0].tv_sec)));
  // lst->args[1] -= tmp;
  if (lst->args[1] <= 0)
    return (print_message(&lst->shared_mutex[0], lst->args[1], lst->philo_id, 4));
  else
    return (print_message(&lst->shared_mutex[0], lst->args[1], lst->philo_id, 2));
}

void *think_routine(void *arg)
{
  t_philo         *lst;

  lst = (t_philo *) arg;
  while (*lst->start_ptr)
    ;
  pthread_mutex_lock(&((t_philo *)arg)->shared_mutex[0]);
  printf("thread nb %ld, index = %d from think\n", lst->philo_id, lst->index);
  pthread_mutex_unlock(&lst->shared_mutex[0]);
  return (NULL);
}

void  *launcher(void *arg)
{
  t_philo *curr_philo;

  curr_philo = (t_philo *) arg;
  if (curr_philo->index % 2 == 0)
    sleep_routine(curr_philo);
  else
    eat_routine(curr_philo);
}

bool  launch_threads(t_philo *lst)
{
  t_philo *head_lst;

  head_lst = lst;
  while (lst)
  {
    if (pthread_create(&(lst)->philo_id, NULL, launcher, lst))
      return (1);
    lst = lst->next;
  }
  return (0);
}

/*
  * philo struct need a timeval tab (like in sleep routine)
  *
*/

int	main(int argc, char **argv)
{
	int			  tab_arg[5];
	t_philo		*head_lst;

	if (argc != 5 && argc != 6)
		return (printf("Nb of arguments is invalid\n"), 0);
	if (parsing(argc, argv, tab_arg))
		return (0);
  if (argc == 5)
	{
    head_lst = socrate_maker(tab_arg);
    t_philo *tmp = head_lst->next;
		if (!head_lst)
        return (0);
    if (launch_threads(head_lst->next))
        return (free_lst(head_lst), 0);
    sleep_routine(head_lst);
    while (tmp)
    {
      pthread_join(tmp->philo_id, NULL);
      tmp = tmp->next;
    }
    free_lst(head_lst);
	}
	return (0);
}

	/*
	if (tab_arg[1] < tab_arg[2] || tab_arg[1] < tab_arg[3])
		// incoherent argument
	else
		// eat %d time and die
	*/
