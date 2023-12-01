/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:07:02 by hbaduel           #+#    #+#             */
/*   Updated: 2023/09/04 17:07:26 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	ft_veriflimiter(char *read, char *limiter)
{
	int	i;
	int	sread;
	int	slimiter;

	i = 0;
	slimiter = ft_strlen(limiter);
	sread = ft_strlen(read);
	if (sread != slimiter)
	{
		if (read[slimiter] != '\n')
			return (1);
	}
	while (i < slimiter)
	{
		if (limiter[i] != read[i])
			return (1);
		i++;
	}
	return (0);
}

void	ft_readterminal(char *limiter, int *tubefd)
{
	char	*terminal;

	close(tubefd[0]);
	while (1)
	{
		terminal = get_next_line(0);
		if (ft_veriflimiter(terminal, limiter) == 0)
		{
			free(terminal);
			exit(0);
		}
		ft_putstr_fd(terminal, tubefd[1]);
		free(terminal);
	}
}

void	ft_heredoc(char *limiter, char **envp)
{
	pid_t	pid;
	int		tubefd[2];

	if (pipe(tubefd) == -1)
		ft_exiterror("ERROR : Pipe error\n", 0);
	pid = fork();
	if (pid == -1)
		ft_exiterror("ERROR : Fork error\n", 0);
	if (pid == 0)
		ft_readterminal(limiter, tubefd);
	waitpid(pid, NULL, 0);
	close(tubefd[1]);
	dup2(tubefd[0], 0);
}
