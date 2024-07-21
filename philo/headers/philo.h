/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:54:39 by florian           #+#    #+#             */
/*   Updated: 2024/07/21 13:24:28 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include "struct.h"

//  ==== main/utils.c ====  //
int			ft_perror(const char *str);
void		*ft_calloc(size_t nmemb, size_t size);
void		free_all(t_philo *philo_tab, int tab_size, t_main_th *main_th);

//  ==== check_args/check_args.c ====  //
int			check_args(int argc, char **argv, int *tab_arg);

// ==== main/init.c ====  //
void		socrate_maker(t_main_th *main_th, int tab_args[], int argc);
int			init_main_thread(t_main_th *main_th, int nb_philo, int argc);

// ==== simulation/philo.c ====  //
void		*routine(void *arg);

//  ==== check_args/check_utils.c ====  //
long		ft_atoi(const char *nptr);

//  ==== simulation/actions.c ====  //
bool		print_message(char *msg, t_philo *philo);
bool		take_forks(t_philo *philo);
bool		drop_forks(t_philo *philo);

//  ==== simulaation/simu_utils.c ====  //
bool		change_death_status(t_philo *philo);
long int	get_time(void);
bool		check_death(t_philo *philo);
int			update_time(t_philo *philo);

#endif
