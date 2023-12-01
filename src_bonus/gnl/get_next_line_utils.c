/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:37:57 by hbaduel           #+#    #+#             */
/*   Updated: 2023/02/18 17:29:49 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_reduce(char	*file)
{
	char	*reduced;
	size_t	len;
	size_t	i;

	len = 0;
	while (file[len] != '\0' && file[len] != '\n')
		len++;
	if (file[len] == '\0' || (file[len] == '\n' && file[len + 1] == '\0'))
	{
		free(file);
		return (NULL);
	}
	reduced = malloc(sizeof(char) * (ft_strlen(file) - len + 1));
	if (!reduced)
		return (NULL);
	i = 0;
	while (file[len + 1] != '\0')
	{
		reduced[i] = file[len + 1];
		i++;
		len++;
	}
	reduced[i] = '\0';
	free(file);
	return (reduced);
}

static char	*ft_select2(char *file, char *line)
{
	size_t	i;

	i = 0;
	while (file[i] != '\n' && file[i] != '\0')
	{
		line[i] = file[i];
		i++;
	}
	if (file[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_select(char *file)
{
	char	*line;
	size_t	i;

	i = 0;
	if (file[i] == '\0')
		return (NULL);
	while (file[i] != '\n' && file[i] != '\0')
		i++;
	if (file[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	return (ft_select2(file, line));
}

char	*ft_strjoin_modif(char *file, char *letters)
{
	char	*joined;
	size_t	i;
	size_t	j;

	joined = malloc(sizeof(char) * (ft_strlen(file) + ft_strlen(letters) + 1));
	if (!joined)
		return (NULL);
	i = 0;
	j = 0;
	while (file[i] != '\0')
	{
		joined[i] = file[i];
		i++;
	}
	while (letters[j] != '\0')
	{
		joined[i + j] = letters[j];
		j++;
	}
	joined[i + j] = '\0';
	free(letters);
	free(file);
	return (joined);
}
