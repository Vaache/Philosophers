/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthreads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 21:32:18 by vhovhann          #+#    #+#             */
/*   Updated: 2023/07/14 13:55:43 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	help(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->mutex_write);
	if (!is_die(philo))
		printf("[%d] : [%lld] %s", philo->id + 1, get_time(), str);
	pthread_mutex_unlock(philo->mutex_write);
}

void	*philo_action(t_philo	*philo)
{
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!is_die(philo))
	{
		pthread_mutex_lock(philo->mutex_right);
		help(philo, "Has Take A Right Fork\n");
		pthread_mutex_lock(philo->mutex_left);
		help(philo, "Has Take A Left Fork\n");
		help(philo, "Is Eating\n");
		pthread_mutex_lock(&philo->mutex_last_eat);
		philo->last_eat = get_time();
		pthread_mutex_unlock(&philo->mutex_last_eat);
		my_usleep(philo->time_eat, philo);
		pthread_mutex_lock(&philo->mutex_eat);
		philo->count_must_eat++;
		pthread_mutex_unlock(&philo->mutex_eat);
		pthread_mutex_unlock(philo->mutex_right);
		pthread_mutex_unlock(philo->mutex_left);
		help(philo, "Is Sleaping\n");
		my_usleep(philo->time_sleep, philo);
		help(philo, "Is Thinking\n");
	}
	return (NULL);
}

void	create_pthread(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->count_philos)
	{
		pthread_create(&(main->philos[i].philo), NULL, \
			(t_phtread_help)philo_action, &main->philos[i]);
		i++;
	}
	while (1)
	{
		if (check_die_philo(main) == 1 || eat_die_check(main) == 1)
			break ;
	}
	i = 0;
	while (i < main->count_philos && main->count_philos > 1)
	{
		pthread_join(main->philos[i].philo, NULL);
		i++;
	}
}

int	check_die_philo(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->count_philos)
	{
		pthread_mutex_lock(&main->philos[i].mutex_last_eat);
		if (get_time() - main->philos[i].last_eat > main->time_die)
		{
			pthread_mutex_lock(main->philos[i].mutex_write);
			printf("[%d] : [%lld] Died\n", main->philos[i].id, get_time());
			pthread_mutex_unlock(main->philos[i].mutex_write);
			pthread_mutex_lock(main->philos[i].mutex_die);
			main->die = 1;
			pthread_mutex_unlock(main->philos[i].mutex_die);
			pthread_mutex_unlock(&main->philos[i].mutex_last_eat);
			return (1);
		}
		pthread_mutex_unlock(&main->philos[i].mutex_last_eat);
		i++;
	}
	return (0);
}

int	is_die(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(philo->mutex_die);
	i = *(philo->die);
	pthread_mutex_unlock(philo->mutex_die);
	return (i);
}
