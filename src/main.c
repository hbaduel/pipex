/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:45:57 by hbaduel           #+#    #+#             */
/*   Updated: 2023/04/10 14:47:46 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_cmdpath(char *cmd, char **envp)
{
	pid_t	cpid;
	char	*res;
	char	*path[2];
	int		tubefd[2];

	path[0] = "which";
	path[1] = cmd;
	path[2] = NULL;
	if (pipe(tubefd) == -1)
		ft_exiterror("ERROR : Pipe error\n");
	cpid = fork();
	if (cpid == -1)
		ft_exiterror("ERROR : Fork error\n");
	if (cpid == 0)
	{
		close(tubefd[0]);
		dup2(tubefd[1], 1);
		close(tubefd[1]);
		execve("/usr/bin/which", path, envp);
	}
	waitpid(cpid, NULL, 0);
	close(tubefd[1]);
	res = ft_readfd(tubefd[0]);
	close(tubefd[0]);
	return (res);
}

void	ft_firstcmd(char **argv, int *tubefd, char **envp)
{
	char	*path;
	char	**cmd;
	int		infilefd;

	infilefd = open(argv[1], O_RDONLY, 0777);
	if (infilefd < 0)
		ft_exiterror("ERROR : Open error for infile\n");
	dup2(infilefd, 0);
	dup2(tubefd[1], 1);
	close(tubefd[0]);
	cmd = ft_split(argv[2], ' ');
	path = ft_cmdpath(cmd[0], envp);
	if (execve(path, cmd, envp) == -1)
	{
		close(tubefd[1]);
		close(infilefd);
		ft_freeargs(cmd);
		free(path);
		ft_exiterror("ERROR : First command not found\n");
	}
}

void	ft_secondcmd(char **argv, int *tubefd, char **envp)
{
	char	*path;
	char	**cmd;
	int		outfilefd;

	outfilefd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfilefd < 0)
		ft_exiterror("ERROR : Open error for outfile\n");
	dup2(tubefd[0], 0);
	dup2(outfilefd, 1);
	close(tubefd[1]);
	cmd = ft_split(argv[3], ' ');
	path = ft_cmdpath(cmd[0], envp);
	if (execve(path, cmd, envp) == -1)
	{
		close(tubefd[0]);
		close(outfilefd);
		ft_freeargs(cmd);
		free(path);
		ft_exiterror("ERROR : Second command not found\n");
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		tubefd[2];
	pid_t	pid;

	if (argc != 5)
		ft_exiterror("ERROR : Please respect <infile cmd cmd outfile>\n");
	if (pipe(tubefd) < 0)
		ft_exiterror("ERROR : Pipe error\n");
	pid = fork();
	if (pid == -1)
		ft_exiterror("ERROR : Fork error\n");
	if (pid == 0)
		ft_firstcmd(argv, tubefd, envp);
	waitpid(pid, NULL, 0);
	pid = fork();
	if (pid == -1) 
		ft_exiterror("ERROR : Fork error\n");
	if (pid == 0)
		ft_secondcmd(argv, tubefd, envp);
	close(tubefd[0]);
	close(tubefd[1]);
	waitpid(pid, NULL, 0);
	return (0);
}
