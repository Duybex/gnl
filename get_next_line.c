/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohen <acohen@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:37:01 by acohen            #+#    #+#             */
/*   Updated: 2024/08/05 18:59:21 by acohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_loop(int fd, char *buff, char *current)
{
	int	bytes;

	bytes = 1;
	while (bytes > 0)
	{
		bytes = read (fd, buff, BUFFER_SIZE);
		if (bytes < 0 || (bytes == 0 && ft_strlen(buff) == 0 && !current[0]))
		{
			free (current);
			return (NULL);
		}
		buff[bytes] = '\0';
		current = free_and_strjoin(current, buff);
		if (current == NULL)
			return (NULL);
		if (ft_strchr (current, '\n'))
			break ;
	}
	return (current);
}

char	*read_txt_file(int fd, char *current)
{
	char	*buff;

	if (current == NULL)
		current = ft_calloc(1, 1);
	if (current == NULL)
		return (NULL);
	buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (buff == NULL)
	{
		free (current);
		return (NULL);
	}
	current = read_loop(fd, buff, current);
	free (buff);
	return (current);
}

char	*get_one_line(char *current)
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
		return (NULL);
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
	{
		free (current);
		return (NULL);
	}
	while (current[i1])
		line[i2++] = current[i1++];
	free (current);
	return (line);
}

char	*get_next_line(int fd)
{
	static char		*current = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	current = read_txt_file(fd, current);
	if (current == NULL)
		return (NULL);
	line = get_one_line(current);
	if (line == NULL)
	{
		free (current);
		current = NULL;
		return (NULL);
	}
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