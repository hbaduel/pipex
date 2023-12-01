/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:56:26 by hbaduel           #+#    #+#             */
/*   Updated: 2023/08/31 10:56:30 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdarg.h>
# include "gnl/get_next_line.h"

char	*ft_readfd(int fd);
char	**ft_split(char *s, char c);
void	ft_exiterror(char *error, int nb);
void	ft_heredoc(char *limiter, char **envp);
void	ft_freeargs(char **cmd);
void	ft_putnbr_fd(long nb, int fd);
void	ft_printf_modif(const char *str, ...);
void	ft_putstr_fd(char *str, int fd);
void	ft_putchar_fd(char c, int fd);
int		ft_strcmp(char *s1, char *s2);
int		ft_open(char *filename, int which);

#endif
