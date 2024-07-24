/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohen <acohen@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:37:01 by acohen            #+#    #+#             */
/*   Updated: 2024/07/24 15:51:48 by acohen           ###   ########.fr       */
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
	int		bytes;
	char	*buff;

	if (current == NULL)
		current = ft_calloc(1, 1);
	bytes = 1;
	buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (buff == NULL || current == NULL)
		return (NULL);
	while (bytes > 0)
	{
		bytes = read (fd, buff, BUFFER_SIZE);
		if (bytes < 0 || (!bytes && ft_strlen(buff) == 0 && !current[0]))
		{
			free (buff);
			free (current);
			return (NULL);
		}
		buff[bytes] = '\0';
		current = free_and_strjoin(current, buff);
		if (ft_strchr (current, '\n'))
			break ;
	}
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
	static char		*current[_SC_OPEN_MAX];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read (fd, 0, 0) < 0)
		return (NULL);
	current[fd] = read_txt_file(fd, current[fd]);
	if (current[fd] == NULL)
		return (NULL);
	line = get_one_line(current[fd]);
	current[fd] = del_previous_line(current[fd]);
	return (line);
}

// int	main()
// {
// 	int	fd;
// 	int fd2;
// 	char	*str;
// 	char	*str2;
// 	fd = open ("text", O_RDONLY);
// 	fd2 = open ("text2", O_RDONLY);
// 	str2 = "x";
// 	str = "x";
// 	while (str != NULL && str2 != NULL)
// 	{
// 		if (str != NULL)
// 		str = get_next_line(fd);
// 		if (str2 != NULL)
// 		str2 = get_next_line(fd2);
// 		if (str != NULL)
// 			printf ("%s", str);
// 		if (str2 != NULL)
// 			printf ("%s", str2);
// 		if (str2 != NULL)
// 		free (str2);
// 		if (str != NULL)
// 		free (str);
// 	}
// 	//printf ("\n");
// 	close (fd);
// 	close (fd2);
// 	return (1);

// }