/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 20:47:41 by vhovhann          #+#    #+#             */
/*   Updated: 2023/07/07 20:27:09 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat_die_check(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->count_philos && main->max_eat != -1)
	{
		pthread_mutex_lock(&main->philos[i].mutex_eat);
		if (main->philos[i].count_must_eat >= main->max_eat)
		{
			pthread_mutex_unlock(&main->philos[i].mutex_eat);
			i++;
		}
		else
		{
			pthread_mutex_unlock(&main->philos[i].mutex_eat);
			break ;
		}
	}
	if (i == main->count_philos)
	{
		pthread_mutex_lock(&main->mutex_die);
		main->die = 1;
		pthread_mutex_unlock(&main->mutex_die);
		return (1);
	}
	return (0);
}
