/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:06:22 by vhovhann          #+#    #+#             */
/*   Updated: 2023/07/06 22:27:52 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long int	ft_atoi(const char *str)
{
	long long int	neg;
	long long int	num;

	neg = 1;
	num = 0;
	if (!str)
		return (0);
	while (*str && ((*str == ' ') || *str == '\t' || *str == '\r'
			|| *str == '\f' || *str == '\v' || *str == '\n'))
		++str;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg *= -1;
		++str;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		++str;
	}
	if (*str != '\0')
		return (write(2, "Error : Invalid Numeric", 24));
	return (num * neg);
}
