/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 18:35:09 by vhovhann          #+#    #+#             */
/*   Updated: 2023/07/08 11:46:39 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef void	*(*t_phtread_help)(void *);

typedef struct s_philo
{
	int				id;
	int				last_eat;
	int				time_eat;
	int				time_sleep;
	int				count_must_eat;
	int				*die;
	pthread_t		philo;
	pthread_mutex_t	mutex_eat;
	pthread_mutex_t	mutex_last_eat;
	pthread_mutex_t	*mutex_write;
	pthread_mutex_t	*mutex_left;
	pthread_mutex_t	*mutex_right;
	pthread_mutex_t	*mutex_die;
}	t_philo;

typedef struct s_main
{
	int				die;
	int				max_eat;
	int				time_die;
	int				count_philos;
	t_philo			*philos;
	pthread_mutex_t	*fork;
	pthread_mutex_t	mutex_write;
	pthread_mutex_t	mutex_die;
}	t_main;

char			*ft_strjoin(char *s1, char *s2);
char			**ft_split(const char *s, char c);
size_t			ft_strlen(const char *str);
long long int	ft_atoi(const char *str);
void			ft_free(char **str);

char			**check_args(char **av);
int				check_numeric(char **str);

int				main_init(t_main *main, char **str);
void			t_info_init(t_main *main, char **str);
void			forks_init(t_main *main);
long long int	get_time(void);
void			my_usleep(unsigned long sleep, t_philo *philo);

void			*philo_action(t_philo	*philo);
int				check_die_philo(t_main *main);
void			create_pthread(t_main *main);
int				is_die(t_philo *philo);
void			exit_prog(t_main *main);
int				eat_die_check(t_main *main);

#endif
