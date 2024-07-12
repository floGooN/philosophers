/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:17:59 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/12 10:29:09 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include <stdlib.h>

# define TAB_ERROR   "Error -> init philo tab\n"

void	*ft_calloc(size_t nmemb, size_t size);
void	free_all(t_philo *philo_tab, int tab_size);
int		print_error(char *str);

#endif
