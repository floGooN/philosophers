/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:17:30 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/17 15:50:59 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int preapare_init(pthread_mutex_t **forks_mtx, \
                        pthread_mutex_t **print_mtx, \
                        pthread_mutex_t **print_watch, int nb_philo)
{
    int i;

    i = 0;
    *forks_mtx = malloc(sizeof(pthread_mutex_t) * nb_philo);
    if (!*forks_mtx)
        return (ft_perror("error -> init_mtx\n"), -1);
    *print_mtx = malloc (sizeof(pthread_mutex_t));
    if (!print_mtx)
        return (free(*forks_mtx), ft_perror("error -> init_mtx\n"), -1);
    pthread_mutex_init(*print_mtx, NULL);
    pthread_mutex_init(*print_watch, NULL);
    while (i < nb_philo)
    {
        pthread_mutex_init(&(forks_mtx[0][i]), NULL);
        i++;
    }
    return (0);
}

static t_philo *init_mtx(t_philo *philo_tab, t_main_th *main_th, int nb_philo)
{
    pthread_mutex_t *forks_mtx;
    pthread_mutex_t *print;
    pthread_mutex_t *print_watch;
    int             i;

    i = 0;
    if (preapare_init(&forks_mtx, &print, &print_watch, nb_philo) == -1)
        return (free(philo_tab), NULL);
    while (i < nb_philo)
    {
        philo_tab[i].shared_mtx.prt_mtx_watch = print_watch;
        philo_tab[i].shared_mtx.print_mtx = print;
        philo_tab[i].shared_mtx.ready_mtx = &main_th->ready_mutex;
        philo_tab[i].shared_mtx.isdead_mtx = &main_th->isdead_mutex;
        philo_tab[i].shared_mtx.right_fork = &forks_mtx[i];
        if (i == nb_philo - 1)
            philo_tab[i].shared_mtx.left_fork = &forks_mtx[0];
        else
            philo_tab[i].shared_mtx.left_fork = &forks_mtx[i + 1];
        i++;
    }
    main_th->print = print;
    main_th->all_forks = forks_mtx;
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
    t_philo *philo_tab;
    int     nb_philo;
    int     i;

    i = 0;
    nb_philo = tab_arg[0];
    philo_tab = ft_calloc(nb_philo, sizeof(t_philo));
    if (!philo_tab)
        return (ft_perror("error -> init tab_philo"), NULL);
    while (i < nb_philo)
    {
        philo_tab[i].index = i + 1;
        philo_tab[i].ready = &(main_th->ready);
        philo_tab[i].is_dead = &(main_th->is_dead);
        philo_tab[i].print = &(main_th->print);
        philo_tab[i].right_fork = 1;
        if (i == nb_philo - 1)
            philo_tab[i].left_fork = &(philo_tab[0].right_fork);
        else
            philo_tab[i].left_fork = &(philo_tab[i + 1].right_fork);
        init_time(&philo_tab[i].time_data, tab_arg, nb_meal);
        i++;
    }
    return (init_mtx(philo_tab, main_th, nb_philo));
}

void  init_main_thread(t_main_th *main_th)
{
    main_th->ready = 0;
    main_th->is_dead = 0;
    main_th->print = 1;
    pthread_mutex_init(&main_th->ready_mutex, NULL);
    pthread_mutex_init(&main_th->isdead_mutex, NULL);
}
