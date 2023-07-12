/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:58:07 by vhovhann          #+#    #+#             */
/*   Updated: 2023/07/01 14:03:42 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_free_split(char **s, size_t i)
{
	while (i-- >= 0)
		free (s[i]);
	free(s);
}

static	size_t	ft_str_word(const char *s, char c)
{
	size_t	i;
	size_t	nw;
	size_t	prev_del;

	i = 0;
	nw = 0;
	prev_del = 1;
	while (s[i])
	{
		if (s[i] == c)
			prev_del = 1;
		else if (prev_del)
		{
			nw++;
			if (s[i] != c)
				prev_del = 0;
		}
		i++;
	}
	return (nw);
}

static char	*ft_sub_str1(char const *s, unsigned int start, size_t len)
{
	size_t	j;
	size_t	k;
	size_t	i;
	char	*str;

	j = 0;
	i = 0;
	if (!s)
		return (0);
	k = ft_strlen(s);
	str = (char *)malloc(len + 1);
	if (!str)
		return (0);
	i = start;
	while (i < k && j < len)
		str[j++] = s[i++];
	str[j] = '\0';
	return (str);
}

static char	**ft_chek_arr(const char *s, char c, char **arr)
{
	size_t	i;
	size_t	k;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			k = 0;
			while (*s && *s != c && ++k)
				++s;
			arr[i++] = ft_sub_str1(s - k, 0, k);
			if (!arr)
			{
				ft_free_split(arr, i);
				return (NULL);
			}
		}
		else
			s++;
	}
	arr[i] = 0;
	return (arr);
}

char	**ft_split(const char *s, char c)
{
	char	**arr;

	if (!s)
		return (NULL);
	arr = (char **)malloc((ft_str_word(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	arr = ft_chek_arr(s, c, arr);
	return (arr);
}
