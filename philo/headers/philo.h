/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:54:39 by florian           #+#    #+#             */
/*   Updated: 2024/07/19 17:43:39 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <struct.h>

//  ==== main/utils.c ====  //
int			ft_perror(const char *str);
void		*ft_calloc(size_t nmemb, size_t size);
void		free_all(t_philo *philo_tab, int tab_size, t_main_th *main_th);
int         stop_simu(t_philo *philo_tab, t_main_th *main_th);

//  ==== check_args/check_args.c ====  //
int			check_args(int argc, char **argv, int *tab_arg);

// ==== main/init.c ====  //
t_philo		*socrate_maker(t_main_th *main_th, int tab_args[], bool nbmeal_flag);
void        init_main_thread(t_main_th *main_th, int nb_philo, int argc);

// ==== simulation/philo.c ====  //
void		*routine(void *arg);

//  ==== check_args/check_utils.c ====  //
long		ft_atoi(const char *nptr);

//  ==== simulation/actions.c ====  //
bool		print_message(char *msg, t_philo *philo, bool is_dead);
bool        take_forks(t_philo *philo);
bool        drop_forks(t_philo *philo);

//  ==== simulaation/simu_utils.c ====  //
bool        am_i_dead(t_philo *philo);
bool		change_death_status(t_philo *philo);
long int	get_time(void);
bool		check_death(t_philo *philo);
int			update_time(t_philo *philo);

#endif
