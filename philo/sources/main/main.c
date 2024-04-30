/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:06:29 by fberthou          #+#    #+#             */
/*   Updated: 2024/04/30 21:51:07 by florian          ###   ########.fr       */
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

void *routine(void *arg)
{
  t_philo         *lst;
  pthread_mutex_t mutex;

  pthread_mutex_init(&mutex, NULL);
  pthread_mutex_lock(&mutex);
  lst = arg;
  while (lst->next)
  {
    lst = lst->next;
  }
  printf("thread nb %ld\n", lst->philo_id);
  pthread_mutex_unlock(&mutex);
  return (NULL);
}

bool  launch_threads(t_philo *lst)
{
  t_philo *head_lst;

  head_lst = lst;
  while (lst)
  {
    if (pthread_create(&(lst)->philo_id, NULL, routine, head_lst))
      return (1);
    lst = lst->next;
  }
  return (0);
}

int	main(int argc, char **argv)
{
	int			  tab_arg[5];
	t_philo		*head_lst;

	if (argc != 5 && argc != 6)
		return (print_error("Nb of arguments is invalid\n"), 0);
	if (parsing(argc, argv, tab_arg))
		return (0);
  if (argc == 5)
	{
    head_lst = socrate_maker(tab_arg);
		if (!head_lst)
        return (0);

    if (launch_threads(head_lst))
        return (free_lst(head_lst), 0);
    free_lst(head_lst);

  /*  create all philosophers before launch all threads

      // if (pthread_create(&lst->philo_id, NULL, start_routine, tab_args))
      // 	return (NULL);

  */
		// if (join_all(head_lst)) // error -> all is free ?
		// 	return (0); // need check memory before exit ?
	}



	// if (tab_arg[0] == 1)
	// {
	// 	th = (pthread_t *) sleep_and_die(tab_arg);
	// 	if (th)
	// 		return (pthread_join(th, NULL), 0);
  //   else
  //     return (print_error("Crash thread initialisation\n"), 0);
	// }




	/*
	if (tab_arg[1] < tab_arg[2] || tab_arg[1] < tab_arg[3])
		// incoherent argument
	else
		// eat %d time and die
	*/
	return (0);
}
