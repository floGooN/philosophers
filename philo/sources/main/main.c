/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:06:29 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/16 10:34:26 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static bool launcher(t_philo *philo_tab, int tab_size)
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

static int main_routine(t_main_th *main_th)
{
    pthread_mutex_lock(&main_th->ready_mutex);
    main_th->ready = 1;
    pthread_mutex_unlock(&main_th->ready_mutex);
    while (1)
    {
      pthread_mutex_lock(&main_th->isdead_mutex);
      if (main_th->is_dead)
      {
        pthread_mutex_unlock(&main_th->isdead_mutex);
        break;
      }
      pthread_mutex_unlock(&main_th->isdead_mutex);
    }
    return (0);
}

int	main(int argc, char **argv)
{
    int         tab_arg[5];
    t_philo     *philo_tab;
    t_main_th   main_th;

    if (argc != 5 && argc != 6)
        return (print_error("Nb of arguments is invalid\n"), 1);
    if (check_args(argc, argv, tab_arg))
        return (2);
    init_main_thread(&main_th);
    if (argc == 5)
        philo_tab = socrate_maker(&main_th, tab_arg, 0);
    else
        philo_tab = socrate_maker(&main_th, tab_arg, 1);
    if (!philo_tab)
        return (3);
    if (launcher(philo_tab, tab_arg[0]))
        return (free_all(philo_tab, tab_arg[0]), 4);
    if (main_routine(&main_th))
        return (5);
    usleep(5000);
    free_all(philo_tab, tab_arg[0]);
    return (0);
}
