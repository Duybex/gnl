/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohen <acohen@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:37:01 by acohen            #+#    #+#             */
/*   Updated: 2024/07/22 14:16:08 by acohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_and_strjoin(char *current, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(current, buffer);
	free (current);
	return (temp);
}

char	*read_txt_file(int fd, char *current)
{
	int		read_bytes;
	char	*buffer;

	if (!current)
		current = ft_calloc(1, 1);
	read_bytes = 1;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (buffer == NULL || current == NULL)
		return (NULL);
	while (read_bytes > 0 && ft_strchr (current, '\n') == NULL)
	{
		read_bytes = read (fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0 && ft_strlen(buffer) == 0 && current[0] == 0)
		{
			free (buffer);
			free (current);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		current = free_and_strjoin(current, buffer);
	}
	free (buffer);
	return (current);
}

char	*get_line(char *current)
{
	int		i1;
	int		i2;
	char	*line;

	i1 = 0;
	i2 = 0;
	while (current[i1] && current[i1] != '\n')
		i1++;
	if (current[i1] == '\n')
		i1++;
	line = ft_calloc(i1 + 1, sizeof(char));
	if (line == NULL)
	{
		return (NULL);
	}
	while (i2 <= i1 - 1)
	{
		line[i2] = current[i2];
		i2++;
	}
	line[i2] = '\0';
	return (line);
}

char	*del_previous_line(char *current)
{
	char	*line;
	int		i1;
	int		i2;

	i1 = 0;
	i2 = 0;
	while (current[i1] && current[i1] != '\n')
		i1++;
	if (current[i1] == '\0')
	{
		free (current);
		return (NULL);
	}
	i1++;
	line = ft_calloc(ft_strlen(current) - i1 + 1, sizeof (char));
	if (line == NULL)
		return (NULL);
	while (current[i1])
		line[i2++] = current[i1++];
	free (current);
	return (line);
}

char	*get_next_line(int fd)
{
	static char		*current;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		return (NULL);
	}
	current = read_txt_file(fd, current);
	if (current == NULL)
	{
		return (NULL);
	}
	line = get_line(current);
	current = del_previous_line(current);
	return (line);
}

// int	main()
// {
// 	int	fd;
// 	char	*str;
// 	fd = open ("text", O_RDONLY);

// 	str = "x";
// 	while (str != NULL)
// 	{
// 		str = get_next_line(fd);
// 		if (str != NULL)
// 			printf ("%s", str);
// 		free (str);
// 	}
// 	//printf ("\n");
// 	close (fd);
// 	return (1);

// }