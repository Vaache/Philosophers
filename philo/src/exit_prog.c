/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:11:56 by vhovhann          #+#    #+#             */
/*   Updated: 2023/07/06 22:27:50 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_prog(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->count_philos)
	{
		pthread_mutex_destroy(&main->fork[i]);
		pthread_mutex_destroy(&(main->philos[i].mutex_eat));
		pthread_mutex_destroy(&(main->philos[i].mutex_last_eat));
		i++;
	}
	pthread_mutex_destroy(&main->mutex_die);
	pthread_mutex_destroy(&main->mutex_write);
	free(main->philos);
	free(main->fork);
}
