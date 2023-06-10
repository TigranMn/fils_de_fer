/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:16:18 by tmnatsak          #+#    #+#             */
/*   Updated: 2023/05/27 14:09:18 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*ft_strdup(const char *s1)
{
	size_t	strlen;
	void	*ptr;

	strlen = ft_strlen(s1) + 1;
	ptr = (char *)malloc(strlen);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1, strlen);
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*joined;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	joined = (char *)malloc(s1len + s2len + 1);
	if (!joined)
		return (NULL);
	ft_strlcpy(joined, s1, s1len + 1);
	ft_strlcat(joined + s1len, s2, s2len + 1);
	free((char *)s1);
	return (joined);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size)
	{
		while (i < (size - 1) && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	dstlen;

	srclen = ft_strlen(src);
	if (!dst && dstsize == 0)
		return (srclen);
	dstlen = ft_strlen(dst);
	if (dstlen >= dstsize)
		return (dstsize + srclen);
	if (srclen < dstsize - dstlen)
		ft_strlcpy(dst + dstlen, src, srclen + 1);
	else
		ft_strlcpy(dst + dstlen, src, dstsize - dstlen);
	dst[dstsize - 1] = '\0';
	return (dstlen + srclen);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
