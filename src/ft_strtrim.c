/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:04:53 by tmnatsak          #+#    #+#             */
/*   Updated: 2023/05/27 23:54:34 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	ft_check(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*trimmed;

	i = 0;
	if (!s1)
		return (NULL);
	j = ft_strlen(s1);
	while (ft_check(set, s1[i]) == 1)
		i++;
	while (ft_check(set, s1[j - 1]) == 1 && i < j)
		j--;
	trimmed = (char *)malloc(j - i + 1);
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, &s1[i], j - i + 1);
	return (trimmed);
}
