/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 13:05:21 by vhovhann          #+#    #+#             */
/*   Updated: 2023/07/06 22:49:30 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		free(str[i++]);
	free(str);
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

void	my_usleep(unsigned long sleep, t_philo *philo)
{
	unsigned long	value;

	value = get_time();
	while (!is_die(philo))
	{
		if (get_time() - value <= sleep)
			usleep(50);
		else
			break ;
	}
}
