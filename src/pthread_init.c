/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:20:16 by vhovhann          #+#    #+#             */
/*   Updated: 2023/07/06 22:19:46 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main_init(t_main *main, char **str)
{
	main->count_philos = ft_atoi(str[0]);
	if (main->count_philos == 0)
		return (1);
	main->time_die = ft_atoi(str[1]);
	if (str[4])
		main->max_eat = ft_atoi(str[4]);
	else
		main->max_eat = -1;
	main->die = 0;
	main->philos = (t_philo *)malloc(sizeof(t_philo) * main->count_philos);
	main->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
		* main->count_philos);
	pthread_mutex_init(&main->mutex_die, NULL);
	pthread_mutex_init(&main->mutex_write, NULL);
	return (0);
}

void	t_info_init(t_main *main, char **str)
{
	int	i;

	i = 0;
	while (i < main->count_philos)
	{
		main->philos[i].id = i;
		main->philos[i].last_eat = 0;
		main->philos[i].time_eat = ft_atoi(str[2]);
		main->philos[i].time_sleep = ft_atoi(str[3]);
		main->philos[i].count_must_eat = 0;
		main->philos[i].die = &(main->die);
		main->philos[i].mutex_die = &(main->mutex_die);
		main->philos[i].mutex_write = &(main->mutex_write);
		pthread_mutex_init(&(main->philos[i].mutex_eat), NULL);
		pthread_mutex_init(&(main->philos[i].mutex_last_eat), NULL);
		i++;
	}
}

void	forks_init(t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->count_philos)
		pthread_mutex_init(&(main->fork[i]), NULL);
	i = 0;
	while (i < main->count_philos)
	{
		if (i == main->count_philos - 1)
		{
			main->philos[i].mutex_left = &main->fork[i];
			main->philos[i].mutex_right = &main->fork[0];
		}
		else
		{
			main->philos[i].mutex_left = &main->fork[i];
			main->philos[i].mutex_right = &main->fork[i + 1];
		}
		i++;
	}
}
