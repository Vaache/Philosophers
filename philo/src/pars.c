/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 13:13:51 by vhovhann          #+#    #+#             */
/*   Updated: 2023/07/05 16:20:48 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			return (write(2, "Error : Larger Lenght Numeric", 30));
		if (ft_atoi(str[i]) > 2147483647)
			return (write(2, "Error : Larger Maximum Integer\n", 32));
		i++;
	}
	i = 0;
	while (str && str[i])
		i++;
	if (i < 4 || i > 5)
		return (write(2, "Error : Quantity Arguments\n", 28));
	return (0);
}
