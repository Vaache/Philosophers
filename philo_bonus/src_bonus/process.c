/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:04:06 by vhovhann          #+#    #+#             */
/*   Updated: 2023/07/14 15:07:29 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	terminate(t_main *main)
{
	int	i;
	int	status;

	i = 0;
	while (i < main->count_philos)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) > 0)
		{
			i = -1;
			while (++i < main->count_philos)
				kill(main->philos[i].pid, SIGKILL);
			break ;
		}
		i++;
	}
}

void	*check_die(t_merg *merg)
{
	while (1)
	{
		sem_wait(merg->philo->sem_last_eat);
		if (get_time() - merg->philo->last_eat > merg->main->time_die)
		{
			sem_wait(merg->philo->sem_write);
			printf("[%d] : [%lld] %s\n", merg->philo->id + 1, \
				get_time(), "Is Death");
			sem_post(merg->philo->sem_last_eat);
			exit(EXIT_FAILURE);
		}
		sem_post(merg->philo->sem_last_eat);
		sem_wait(merg->philo->sem_each_eat);
		if (merg->philo->count_must_eat == merg->main->max_eat && \
			merg->main->max_eat != -1)
		{
			sem_post(merg->philo->sem_each_eat);
			break ;
		}
		sem_post(merg->philo->sem_each_eat);
	}
	return (NULL);
}

void	forks(t_main *main, int i)
{
	t_philo	*philo;
	t_merg	merg;

	philo = &main->philos[i];
	merg.main = main;
	merg.philo = philo;
	pthread_create(&philo->philo, NULL, (t_phtread_help)check_die, &merg);
	if (main->philos[i].id % 2 == 0)
		usleep(1000);
	while (1)
	{
		forks2(philo);
		if (philo->count_must_eat == main->max_eat && main->max_eat != -1)
		{
			sem_post(philo->sem_each_eat);
			break ;
		}
		sem_post(philo->sem_each_eat);
		printf("[%d] : [%lld] %s\n", i + 1, get_time(), "Is Selaping");
		sem_post(philo->sem_write);
		my_usleep(philo->time_sleep);
		sem_wait(philo->sem_write);
		printf("[%d] : [%lld] %s\n", i + 1, get_time(), "Is Thinking");
		sem_post(philo->sem_write);
	}
	pthread_join(philo->philo, NULL);
	exit(1);
}

void	forks2(t_philo *philo)
{
	sem_wait(philo->sem_fork);
	sem_wait(philo->sem_write);
	printf("[%d] : [%lld] %s\n", philo->id + 1, get_time(), \
		"Has Take A Right Fork");
	sem_post(philo->sem_write);
	sem_wait(philo->sem_fork);
	sem_wait(philo->sem_write);
	printf("[%d] : [%lld] %s\n", philo->id + 1, get_time(), \
		"Has Take A Left Fork");
	sem_post(philo->sem_write);
	sem_wait(philo->sem_write);
	printf("[%d] : [%lld] %s\n", philo->id + 1, get_time(), \
		"Is Eating");
	sem_post(philo->sem_write);
	sem_wait(philo->sem_last_eat);
	philo->last_eat = get_time();
	sem_post(philo->sem_last_eat);
	my_usleep(philo->time_eat);
	sem_wait(philo->sem_each_eat);
	philo->count_must_eat++;
	sem_post(philo->sem_each_eat);
	sem_post(philo->sem_fork);
	sem_post(philo->sem_fork);
	sem_wait(philo->sem_write);
	sem_wait(philo->sem_each_eat);
}

void	creat_process(t_main *main)
{
	int		i;

	i = 0;
	while (i < main->count_philos)
	{
		main->philos[i].pid = fork();
		main->philos[i].id = i;
		if (main->philos[i].pid < 0)
		{
			perror("fork ");
			exit(EXIT_FAILURE);
		}
		if (main->philos[i].pid == 0)
			forks(main, i);
		i++;
	}
	terminate(main);
}
