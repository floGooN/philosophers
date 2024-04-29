/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:06:29 by fberthou          #+#    #+#             */
/*   Updated: 2024/04/29 21:37:53 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>

#include <unistd.h>

/* ====	PROTOTYPES	==== */
int		parsing(int argc, char **argv, int *tab_arg);
int		print_error(char *str);
void	*ft_calloc(size_t nmemb, size_t size);
/* ====	PROTOTYPES	==== */

void	*sleep_and_die(void *tab_arg)
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
}


typedef struct s_philo
{
	pthread_t		    philo_id;
	int				      *args;

  pthread_mutex_t mutex;
  bool            fork;

	struct s_philo	*next;
}	t_philo ;

void  free_lst(t_philo *head_lst)
{
  t_philo *tmp;

  while (head_lst)
  {
    tmp = head_lst->next;
    free(head_lst);
    head_lst = tmp;
  }
}

bool init_head_lst(t_philo **head, int *tab_args)
{
	*head = ft_calloc(1, sizeof(t_philo));
	if (!*head)
		return (1);
	(*head)->args = tab_args;
	if (pthread_mutex_init(&(*head)->mutex, NULL))
    return (free_lst(*head), 1);
  printf("check init fork : %d, next : %x\n", (*head)->fork, (*head)->next);
  return (0);
}

t_philo	*socrate_maker(int *tab_args)
{
	t_philo	*lst;
	t_philo	*head;
	int 		nb_philo;

  if (init_head_lst(&head, tab_args))
    return (NULL);
	lst = head;
	nb_philo = tab_args[0] - 1;
	while (nb_philo--)
	{
		lst->next = ft_calloc(1, sizeof(t_philo));
		if (!lst->next)
			return (free_lst(head), NULL);
    lst = lst->next;
    lst->args = tab_args;
    if (pthread_mutex_init(&lst->mutex, NULL))
      return (free_lst(head), NULL);
    printf("check init fork : %d, next : %ld\n", head->fork, head->next);
	}
	return (head);
}

int	main(int argc, char **argv)
{
	int			  tab_arg[5];
	t_philo		*head_lst;
  pthread_t th;


	if (argc != 5 && argc != 6)
		return (print_error("Nb of arguments is invalid\n"), 0);
	if (parsing(argc, argv, tab_arg))
		return (0);

	if (tab_arg[0] == 1)
	{
		th = (pthread_t *) sleep_and_die(tab_arg);
		if (th)
			return (pthread_join(th, NULL), 0);
    else
      return (print_error("Crash thread initialisation\n"), 0);
	}



  else if (argc == 5)
	{
  /*  create all philosophers before launch all threads

      // if (pthread_create(&lst->philo_id, NULL, start_routine, tab_args))
      // 	return (NULL);

  */
		head_lst = socrate_maker(tab_arg);
		if (!head_lst)
    	  return (print_error("Crash thread initialisation\n"), 0);
		// if (join_all(head_lst)) // error -> all is free ?
		// 	return (0); // need check memory before exit ?
    free_lst(head_lst);
	}







	/*
	if (tab_arg[1] < tab_arg[2] || tab_arg[1] < tab_arg[3])
		// incoherent argument
	else
		// eat %d time and die
	*/
	return (0);
}
