/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 18:34:52 by vhovhann          #+#    #+#             */
/*   Updated: 2023/07/06 22:22:54 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_valid_av(char **str)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j] == ' ' && str[i][j] != '\0')
			j++;
		if (str[i][j] == '\0')
		{
			write(2, "Error : Invalid Parameter\n", 27);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_valid(char **str)
{
	int	i;
	int	j;

	i = -1;
	while (str && str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (str[i][j] == '+')
				j++;
			if (str[i][j] == '-' && j == 0)
				return (write(2, "Error : Minus Numeric", 22));
			if (str[i][j] == '+' && j != 0)
				return (write(2, "Error : More Pluse\n", 20));
			if (str[i][j] < '0' || str[i][j] > '9')
				return (write(2, "Error : In Arguments\n", 22));
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	char	**str;
	t_main	main;

	get_time();
	if (ac == 5 || ac == 6)
	{
		if (check_valid_av(av) != 0)
			return (0);
		str = check_args(av);
		if (check_valid(str) != 0 || check_numeric(str) != 0)
			return (0);
		if (main_init(&main, str) == 1)
			return (1);
		t_info_init(&main, str);
		forks_init(&main);
		creat_pthread(&main);
		exit_prog(&main);
	}
	else
	{
		write(2, "Error : Wrong Number of Arguments\n", 35);
		return (0);
	}
}
