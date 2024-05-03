/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:17:59 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/03 21:26:31 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include <stdlib.h>

# define MUTEX_ERROR "Error -> init mutex\n"
# define LST_ERROR   "Error -> init list\n"

void	*ft_calloc(size_t nmemb, size_t size);
void  free_philo(t_philo *philo_tab, size_t tab_size);
int		print_error(char *str);

#endif
