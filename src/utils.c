/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:52:57 by hbaduel           #+#    #+#             */
/*   Updated: 2023/08/31 10:53:02 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_freeargs(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

char	*ft_readfd(int fd)
{
	char	*res;
	int		size;

	res = malloc(sizeof(char) * 100);
	if (!res)
		ft_exiterror("ERROR : Malloc error\n");
	size = read(fd, res, 100);
	if (size == -1)
	{
		free(res);
		ft_exiterror("ERROR : Read error\n");
	}
	if (size == 0)
	{
		res[0] = '\0';
		return (res);
	}
	res[size - 1] = '\0';
	return (res);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

void	ft_exiterror(char *error)
{
	ft_putstr_fd(error, 2);
	exit(1);
}
