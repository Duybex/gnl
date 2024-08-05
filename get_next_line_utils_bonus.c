/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohen <acohen@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:55:40 by acohen            #+#    #+#             */
/*   Updated: 2024/08/05 19:01:22 by acohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*free_and_strjoin(char *current, char *buffer)
{
	char	*joint;
	size_t	size;

	size = ft_strlen(current) + ft_strlen(buffer) + 1;
	joint = ft_calloc((size), sizeof(char));
	if (joint == NULL)
	{
		free (current);
		return (NULL);
	}
	ft_strlcat(joint, current, size);
	ft_strlcat(joint, buffer, size);
	free (current);
	return (joint);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			full_size;
	int				i;

	i = 0;
	full_size = nmemb * size;
	if (size != 0)
	{
		if (full_size != 0 && full_size / size != nmemb)
			return (NULL);
	}
	ptr = malloc(size * nmemb);
	if (ptr != NULL)
	{
		while (nmemb--)
			ptr[i++] = 0;
	}
	return (ptr);
}

size_t	ft_strlen(const char *str)
{
	size_t	c;

	c = 0;
	while (str[c] != '\0')
		c++;
	return (c);
}
