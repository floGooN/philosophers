/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:06:29 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/05 09:13:52 by florian          ###   ########.fr       */
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
t_philo	*socrate_maker(int (*tab_args)[5], bool *ready_ptr, bool *is_dead, \
                                        pthread_mutex_t *ready_isdead_mutex);
//t_check *checker_init(size_t tab_size, bool *ready, void **is_dead);

// main/philo.c
void  *odd_routine(void *arg);
void  *even_routine(void *arg);

/* ====	PROTOTYPES	==== */


// void  *checker_routine(void *arg)
// {
//   t_check *checker;

//   checker = (t_check *) arg;
//   pthread_join(checker->th_id, checker->is_dead);
//   return (NULL);
// }

    // check_tab = checker_init(tab_arg[0], &ready, &is_dead);
    // if (!check_tab)
    //   return (free_all(philo_tab, tab_arg[0], NULL), 0);

bool  launcher(t_philo *philo_tab, int tab_size)
{
  int  i;

  i = 0;
  while (i < tab_size)
  {
    if (philo_tab[i].index % 2)
    {
      if (pthread_create(&philo_tab[i].philo_id, NULL, odd_routine, &philo_tab[i]))
        return (1);
    }
    else
    {
      if (pthread_create(&philo_tab[i].philo_id, NULL, even_routine, &philo_tab[i]))
        return (1);
    }
    i++;
  }
  return (0);
}

int	main(int argc, char **argv)
{
  int		          tab_arg[5];
  t_philo         *philo_tab;
  pthread_mutex_t ready_isdead_mutex[2];
  bool            is_dead;
  bool            ready;

  ready = 0;
  is_dead = 0;
  pthread_mutex_init(&ready_isdead_mutex[0], NULL);
  pthread_mutex_init(&ready_isdead_mutex[1], NULL);
  if (argc != 5 && argc != 6)
    return (printf("Nb of arguments is invalid\n"), 0);
  if (parsing(argc, argv, tab_arg)) // init last arg
    return (0);
  if (argc == 5)
  {
    philo_tab = socrate_maker(&tab_arg, &ready, &is_dead, ready_isdead_mutex);
    if (!philo_tab)
        return (0);
    if (launcher(philo_tab, tab_arg[0]))
        return (free_all(philo_tab, tab_arg[0]), 0);
    pthread_mutex_lock(&ready_isdead_mutex[0]);
    usleep(500);
    printf("LAUNCHED\n");
    ready = 1;
    pthread_mutex_unlock(&ready_isdead_mutex[0]);

    while (!is_dead)
      ;
    usleep(500000);
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
