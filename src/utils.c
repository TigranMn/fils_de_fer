/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:42:27 by tmnatsak          #+#    #+#             */
/*   Updated: 2023/06/03 21:36:34 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < 48 || str[i] > 57)
			ft_error("Invalid map");
		i++;
	}
	return (1);
}

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	result;

	result = 0;
	i = 0;
	sign = 1;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + (str[i++] - '0');
	return (result * sign);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	size_t	sub_len;
	char	*sub;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	sub_len = 0;
	if (start < slen)
		sub_len = slen - start;
	else
		return (ft_strdup(""));
	if (sub_len > len)
		sub_len = len;
	sub = (char *)malloc(sizeof(char) * sub_len + 1);
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, (s + start), (sub_len + 1));
	return (sub);
}

void	free_2d_int_arr(int **split, int i)
{
	while (i--)
		free(split[i]);
	free(split);
}
