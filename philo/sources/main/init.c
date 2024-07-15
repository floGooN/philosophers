/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:17:30 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/15 15:12:57 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <struct.h>
#include <philo.h>

static t_philo  *init_tab(int tab_size, pthread_mutex_t **print)
{
  t_philo *tab;

  tab = ft_calloc(tab_size, sizeof(t_philo));
  if (!tab)
    return (print_error("error -> init tab_philo"), NULL);
  *print = malloc(sizeof(pthread_mutex_t));
  if (!*print)
    return (free(tab), print_error("error -> init tab_philo"), NULL);
  pthread_mutex_init(*print, NULL);
  return (tab);
}

t_philo	*socrate_maker(t_main_th *main_th, int tab_arg[])
{
  pthread_mutex_t *print;
	t_philo	        *tab;
  int             i;

  i = -1;
  tab = init_tab(tab_arg[0], &print);
  if (!tab)
    return (NULL);
  while (++i < tab_arg[0])
  {
    tab[i].print_mutex = print;
    tab[i].ready_mutex = &main_th->ready_mutex;
    tab[i].isdead_mutex = &main_th->isdead_mutex;
    pthread_mutex_init(&tab[i].fork_mutex, NULL);
    tab[i].fork = 1;
    tab[i].index = i + 1;
    tab[i].time_data.time_to_die = tab_arg[1];
    tab[i].time_data.nb_meal = -1;
    if (tab_arg[4] > 0)
      tab[i].time_data.nb_meal = tab_arg[4];
    tab[i].ready = &main_th->ready;
    tab[i].is_dead = &main_th->is_dead;
    tab[i].time_data.args = tab_arg;
  }
  return (tab);
}

void  init_main_thread(t_main_th *main_th)
{
    main_th->ready = 0;
    main_th->is_dead = 0;
    pthread_mutex_init(&main_th->ready_mutex, NULL);
    pthread_mutex_init(&main_th->isdead_mutex, NULL);
}
