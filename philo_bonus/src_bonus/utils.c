/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 13:05:21 by vhovhann          #+#    #+#             */
/*   Updated: 2023/07/14 16:04:37 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = ((j = 0));
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	while (s1 && s1[j] != '\0')
	{
		str[i] = s1[i];
		i++;
		j++;
	}
	j = 0;
	while (s2 && s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

long long int	get_time(void)
{
	static int			exec_count;
	static long long	start;
	struct timeval		time;

	if (exec_count == 0)
	{
		gettimeofday(&time, NULL);
		start = (time.tv_usec / 1000) + (time.tv_sec * 1000);
		exec_count ++;
	}
	gettimeofday(&time, NULL);
	return ((time.tv_usec / 1000) + (time.tv_sec * 1000) - start);
}

void	my_usleep(unsigned long sleep)
{
	unsigned long	value;

	value = get_time();
	while (get_time() - value <= sleep)
		usleep(50);
}

void	my_print(t_philo *philo, char *str)
{
	sem_wait(philo->sem_write);
	printf("[%d] : [%lld] %s\n", philo->id + 1, get_time(), str);
	sem_post(philo->sem_write);
}
