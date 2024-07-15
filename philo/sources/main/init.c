/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:17:30 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/15 19:50:23 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <struct.h>
#include <philo.h>

static int preapare_init(pthread_mutex_t **forks_mtx, \
                        pthread_mutex_t **print_mtx, int nb_philo)
{
    int i;

    i = 0;
    *forks_mtx = malloc(sizeof(pthread_mutex_t) * nb_philo);
    if (!*forks_mtx)
        return (print_error("error -> init_mtx\n"), -1);
    *print_mtx = malloc (sizeof(pthread_mutex_t));
    if (!print_mtx)
        return (free(*forks_mtx), print_error("error -> init_mtx\n"), -1);
    while (i < nb_philo)
    {
        pthread_mutex_init(forks_mtx[i], NULL);
        i++;
    }
    pthread_mutex_init(*print_mtx, NULL);
    return (0);
}

static t_philo *init_mtx(t_philo *philo_tab, t_main_th *main_th, int nb_philo)
{
    pthread_mutex_t *forks_mtx;
    pthread_mutex_t *print;
    int             i;

    i = 0;
    if (preapare_init(&forks_mtx, &print, nb_philo) == -1)
        return (NULL);
    while (i < nb_philo)
    {
        philo_tab[i].shared_mtx.print_mtx = print;
        philo_tab[i].shared_mtx.ready_mtx = &main_th->ready_mutex;
        philo_tab[i].shared_mtx.isdead_mtx = &main_th->isdead_mutex;
        philo_tab[i].shared_mtx.right_fork = &forks_mtx[i];
        if (i == nb_philo - 1)
            philo_tab[i].shared_mtx.left_fork = &forks_mtx[0];
        else
            philo_tab[i].shared_mtx.left_fork = &forks_mtx[i + 1];
    }
    return (philo_tab);
}

static void    init_time(t_time *time_data, int tab_arg[], bool nb_meal)
{
    time_data->time_to_die = tab_arg[1];
    time_data->time_to_eat = tab_arg[2];
    time_data->time_to_sleep = tab_arg[3];
    if (nb_meal)
      time_data->nb_meal = tab_arg[4];
    else
      time_data->nb_meal = -1;
    time_data->args = tab_arg;
}

t_philo	*socrate_maker(t_main_th *main_th, int tab_arg[], bool nb_meal)
{
    t_philo *tab;
    int     i;

    i = 0;
    tab = ft_calloc(tab_arg[0], sizeof(t_philo));
    if (!tab)
        return (print_error("error -> init tab_philo"), NULL);
    while (i < tab_arg[0])
    {
        tab[i].index = i + 1;
        tab[i].ready = &(main_th->ready);
        tab[i].is_dead = &(main_th->is_dead);
        tab[i].right_fork = 1;
        if (i == tab_arg[0] - 1)
            tab->left_fork = &tab[0].right_fork;
        else
            tab->left_fork = &tab[i + 1].right_fork;
        init_time(&tab[i].time_data, tab_arg, nb_meal);
        i++;
    }
    return (init_mtx(tab, main_th, tab_arg[0]));
}

void  init_main_thread(t_main_th *main_th)
{
    main_th->ready = 0;
    main_th->is_dead = 0;
    pthread_mutex_init(&main_th->ready_mutex, NULL);
    pthread_mutex_init(&main_th->isdead_mutex, NULL);
}
