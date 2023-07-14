/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 13:13:51 by vhovhann          #+#    #+#             */
/*   Updated: 2023/07/13 16:30:24 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	**check_args(char **av)
{
	int		i;
	char	*str;
	char	**arr;

	i = 1;
	str = NULL;
	while (av[i])
	{
		str = ft_strjoin(str, " ");
		str = ft_strjoin(str, av[i]);
		i++;
	}
	arr = ft_split(str, ' ');
	free(str);
	if (!arr)
		return (NULL);
	return (arr);
}

int	check_numeric(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str && str[i])
	{
		j = 0;
		if (ft_strlen(str[i]) > 10)
			panic("Error : Larger Lenght Numeric");
		if (ft_atoi(str[i]) > 2147483647)
			panic("Error : Larger Maximum Integer\n");
		i++;
	}
	i = 0;
	while (str && str[i])
		i++;
	if (i < 4 || i > 5)
		panic("Error : Quantity Arguments\n");
	return (0);
}
