/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohen <acohen@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:55:40 by acohen            #+#    #+#             */
/*   Updated: 2024/07/17 16:24:09 by acohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

char	*ft_strchr(const char *str, int c)
{
	char	find;

	find = (char) c;
	while (*str != '\0')
	{
		if (*str == find)
			return ((char *)str);
		str++;
	}
	if (find == '\0' && *str == '\0')
		return ((char *)str);
	return (NULL);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	int		i;
	int		cpylen;
	size_t	srclen;

	srclen = ft_strlen (src);
	if (size <= 0)
		return (srclen);
	i = 0;
	if (srclen >= size - 1)
		cpylen = size - 1;
	else
		cpylen = srclen;
	while (i < (cpylen))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	i1;
	size_t	i2;

	srclen = ft_strlen(src);
	dstlen = ft_strlen (dst);
	i1 = 0;
	i2 = 0;
	if (size <= dstlen)
		return (srclen + size);
	while (dst[i1])
		i1++;
	while (src[i2] && (size - dstlen - 1) > i2)
		dst[i1++] = src[i2++];
	dst[i1] = '\0';
	return (srclen + dstlen);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joint;
	size_t	size;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	joint = ft_calloc((size), sizeof(char));
	if (joint == NULL)
		return (NULL);
	ft_strlcpy(joint, s1, ft_strlen(s1) + 1);
	ft_strlcat(joint, s2, size);
	return (joint);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n--)
	{
		*p = (unsigned char)c;
		p++;
	}
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	full_size;

	full_size = nmemb * size;
	if (size != 0)
	{
		if (full_size != 0 && full_size / size != nmemb)
			return (NULL);
	}
	ptr = malloc(size * nmemb);
	if (ptr != NULL)
		ft_memset(ptr, 0, (nmemb * size));
	return (ptr);
}

size_t	ft_strlen(const char *str)
{
	int	c;

	c = 0;
	while (str [c] != '\0')
	{
		c++;
	}
	return (c);
}
