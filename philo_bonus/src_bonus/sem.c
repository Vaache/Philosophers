/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 20:35:57 by vhovhann          #+#    #+#             */
/*   Updated: 2023/07/14 14:43:01 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	main_init(t_main *main, char **str)
{
	t_philo	philo;
	int		i;

	i = 0;
	main->count_philos = ft_atoi(str[0]);
	main->time_die = ft_atoi(str[1]);
	if (ft_atoi(str[4]))
		main->max_eat = ft_atoi(str[4]);
	else
		main->max_eat = -1;
	main->philos = (t_philo *)malloc(sizeof(t_philo) * main->count_philos);
	philo_init(&philo, str, main->count_philos);
	while (i < main->count_philos)
	{
		main->philos[i] = philo;
		i++;
	}
}

void	philo_init(t_philo *philo, char **str, int count_philo)
{
	philo->count_must_eat = 0;
	philo->last_eat = 0;
	philo->time_eat = ft_atoi(str[2]);
	philo->time_sleep = ft_atoi(str[3]);
	semaphores_init(philo, count_philo);
}

void	semaphores_init(t_philo *philo, int count_philo)
{
	sem_unlink(SEM_EACH_EAT);
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_LAST_EAT);
	sem_unlink(SEM_WRITE);
	philo->sem_each_eat = sem_open(SEM_EACH_EAT, O_CREAT, S_IRWXU, 1);
	philo->sem_fork = sem_open(SEM_FORK, O_CREAT, S_IRWXU, count_philo);
	philo->sem_last_eat = sem_open(SEM_LAST_EAT, O_CREAT, S_IRWXU, 1);
	philo->sem_write = sem_open(SEM_WRITE, O_CREAT, S_IRWXU, 1);
	if (philo->sem_each_eat == SEM_FAILED || philo->sem_fork == SEM_FAILED || \
		philo->sem_last_eat == SEM_FAILED || philo->sem_write == SEM_FAILED)
	{
		perror("sem_open");
		exit(EXIT_FAILURE);
	}
}

void	semaphores_close(t_main *main)
{
	sem_close(main->philos->sem_fork);
	sem_close(main->philos->sem_write);
	sem_close(main->philos->sem_last_eat);
	sem_close(main->philos->sem_each_eat);
	sem_unlink(SEM_LAST_EAT);
	sem_unlink(SEM_EACH_EAT);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_FORK);
	free(main->philos);
}
