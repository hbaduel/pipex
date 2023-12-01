/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:56:39 by hbaduel           #+#    #+#             */
/*   Updated: 2023/08/31 10:56:43 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		ft_exiterror("ERROR : Malloc error\n", 0);
	size = read(fd, res, 100);
	if (size == -1)
	{
		free(res);
		ft_exiterror("ERROR : Read error\n", 0);
	}
	if (size == 0)
	{
		res[0] = '\0';
		return (res);
	}
	res[size - 1] = '\0';
	return (res);
}

void	ft_printf_modif(const char *str, ...)
{
	int		i;
	va_list	args;

	i = 0;
	va_start(args, str);
	while (str[i])
	{
		while (str[i] != '%' && str[i] != '\0')
		{
			ft_putchar_fd(str[i], 2);
			i++;
		}
		if (str[i] == '%')
		{
			ft_putnbr_fd((long)va_arg(args, int), 2);
			i += 2;
		}
	}
	va_end(args);
}

int	ft_open(char *filename, int which)
{
	int	fd;

	if (which == 0)
		fd = open(filename, O_RDONLY, 0777);
	else if (which == 1)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd < 0)
		ft_exiterror("ERROR : Open error\n", 0);
	return (fd);
}

void	ft_exiterror(char *error, int nb)
{
	if (nb == 0)
		ft_putstr_fd(error, 2);
	else
		ft_printf_modif(error, nb);
	exit(1);
}
