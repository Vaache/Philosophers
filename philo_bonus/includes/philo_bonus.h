/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 18:35:09 by vhovhann          #+#    #+#             */
/*   Updated: 2023/07/12 22:06:23 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

# define SEM_WAIT		"/sem_wait"
# define SEM_DIE		"/sem_die"
# define SEM_FORK		"/sem_fork"
# define SEM_WRITE		"/sem_write"
# define SEM_LAST_EAT	"/sem_last_eat"
# define SEM_EACH_EAT	"/sem_each_eat"

typedef void	*(*t_phtread_help)(void *);

typedef struct s_philo
{
	pid_t			id;
	int				last_eat;
	int				time_eat;
	int				time_sleep;
	int				count_must_eat;
	pthread_t		philo;
	sem_t			*sem_each_eat;
	sem_t			*sem_die;
	sem_t			*sem_fork;
	sem_t			*sem_write;
	sem_t			*sem_last_eat;
}	t_philo;

typedef struct s_main
{
	int				max_eat;
	int				time_die;
	int				count_philos;
	t_philo			*philos;
}	t_main;

char			*ft_strjoin(char *s1, char *s2);
char			**ft_split(const char *s, char c);
size_t			ft_strlen(const char *str);
long long int	ft_atoi(const char *str);
void			ft_free(char **str);

char			**check_args(char **av);
int				check_numeric(char **str);

long long int	get_time(void);
void			my_usleep(unsigned long sleep, t_philo *philo);

void	main_init(t_main *main, char **str);
void	semaphores_init(t_philo *philo,  int count_philo);
void	philo_init(t_philo *philo, char **str, int count_philo);
#endif
