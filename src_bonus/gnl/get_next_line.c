/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:37:50 by hbaduel           #+#    #+#             */
/*   Updated: 2023/02/19 06:30:06 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_checkendline(char *file)
{
	int	i;

	i = 0;
	while (file[i] != '\0')
	{
		if (file[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_read(int fd)
{
	char	*letters;
	int		resultread;

	letters = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!letters)
		return (NULL);
	resultread = read(fd, letters, BUFFER_SIZE);
	if (resultread == 0 || resultread == -1)
	{
		free(letters);
		return (NULL);
	}
	letters[resultread] = '\0';
	return (letters);
}

char	*ft_mallocsize1(void)
{
	char	*file;

	file = malloc(sizeof(char) * 1);
	if (!file)
		return (NULL);
	file [0] = '\0';
	return (file);
}

char	*get_next_line(int fd)
{
	static char	*file;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (file)
			free(file);
		file = NULL;
		return (NULL);
	}
	if (!file)
		file = ft_mallocsize1();
	while (ft_checkendline(file) == 1)
	{
		line = ft_read(fd);
		if (!line)
			break ;
		file = ft_strjoin_modif(file, line);
		if (!file)
			return (NULL);
	}
	line = ft_select(file);
	file = ft_reduce(file);
	return (line);
}
