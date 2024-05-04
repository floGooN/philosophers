/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:06:29 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/04 13:15:24 by fberthou         ###   ########.fr       */
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
void  free_all(t_philo *philo_tab, int tab_size);

// init/init.c
t_philo	*socrate_maker(int *tab_args, bool *ready_ptr, void **retval, \
                                              pthread_mutex_t *ready_mutex);
//t_check *checker_init(size_t tab_size, bool *ready, void **retval);

// main/philo.c
void  *odd_routine(void *arg);
void  *even_routine(void *arg);

/* ====	PROTOTYPES	==== */


// void  *checker_routine(void *arg)
// {
//   t_check *checker;

//   checker = (t_check *) arg;
//   pthread_join(checker->th_id, checker->retval);
//   return (NULL);
// }

bool  launcher(t_philo *philo_tab)
{
  int  i;

  i = 0;
  while (i++ < philo_tab[0].args[0])
  {
    if (philo_tab->index % 2)
    {
      if (pthread_create(&philo_tab[i].philo_id, NULL, odd_routine, &philo_tab[i]))
        return (1);
      // check_tab[i].th_id = philo_tab[i].philo_id;
      // if (pthread_create(&check_tab[i].th_id, NULL, checker_routine, &check_tab[i]))
      //   return (1);
    }
    else
    {
      if (pthread_create(&philo_tab[i].philo_id, NULL, even_routine, &philo_tab[i]))
        return (1);
      // check_tab[i].th_id = philo_tab[i].philo_id;
      // if (pthread_create(&check_tab[i].th_id, NULL, checker_routine, &check_tab[i]))
      //   return (1);
    }
  }
  return (0);
}

int	main(int argc, char **argv)
{
  int		          tab_arg[5];
  t_philo         *philo_tab;
  void            *retval;
  bool            ready;
  pthread_mutex_t ready_retval_mutex[2];

  ready = 0;
  pthread_mutex_init(&ready_retval_mutex[0], NULL);
  pthread_mutex_init(&ready_retval_mutex[1], NULL);
  retval = NULL;
  if (argc != 5 && argc != 6)
    return (printf("Nb of arguments is invalid\n"), 0);
  if (parsing(argc, argv, tab_arg))
    return (0);
  if (argc == 5)
  {
    philo_tab = socrate_maker(tab_arg, &ready, &retval, ready_retval_mutex);
    if (!philo_tab)
        return (0);
    // check_tab = checker_init(tab_arg[0], &ready, &retval);
    // if (!check_tab)
    //   return (free_all(philo_tab, tab_arg[0], NULL), 0);
    if (launcher(philo_tab))
        return (free_all(philo_tab, tab_arg[0]), 0);
    pthread_mutex_lock(&ready_retval_mutex[0]);
    printf("minisleep 0.5 sec\n");
    usleep(500000);
    ready = 1;
    pthread_mutex_unlock(&ready_retval_mutex[0]);
    while (!retval)
      ;
    sleep(1);
    free_all(philo_tab, tab_arg[0]);
  }
  return (0);
}
	/*
	if (tab_arg[1] < tab_arg[2] || tab_arg[1] < tab_arg[3])
		// incoherent argument
	else
		// eat %d time and die
	*/
