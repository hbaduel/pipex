/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:56:14 by hbaduel           #+#    #+#             */
/*   Updated: 2023/08/31 10:56:18 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		ft_exiterror("ERROR : Pipe error\n", 0);
	cpid = fork();
	if (cpid == -1)
		ft_exiterror("ERROR : Fork error\n", 0);
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

void	ft_execcmd(char *allcmd, int ncmd, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(allcmd, ' ');
	path = ft_cmdpath(cmd[0], envp);
	if (execve(path, cmd, envp) == -1)
	{
		printf("test");
		ft_freeargs(cmd);
		free(path);
		ft_exiterror("ERROR : Command number %d not found\n", ncmd);
	}
}

void	ft_pipe(char *allcmd, int ncmd, char **envp)
{
	pid_t	pid;
	int		tubefd[2];

	if (pipe(tubefd) == -1)
		ft_exiterror("ERROR : Pipe error\n", 0);
	pid = fork();
	if (pid == -1)
		ft_exiterror("ERROR : Fork error\n", 0);
	if (pid == 0)
	{
		close(tubefd[0]);
		dup2(tubefd[1], 1);
		ft_execcmd(allcmd, ncmd, envp);
	}
	waitpid(pid, NULL, 0);
	close(tubefd[1]);
	dup2(tubefd[0], 0);
}

void	ft_nextcmd(char **argv, int argc, int outfilefd, char **envp)
{
	pid_t	pid;
	int		ncmd;
	int		arg;

	if (ft_strcmp(argv[1], "here_doc") == 0)
		arg = 3;
	else
		arg = 2;
	ncmd = 1;
	while (arg < argc - 2)
	{
		ft_pipe(argv[arg], ncmd, envp);
		arg++;
		ncmd++;
	}
	pid = fork();
	if (pid == -1)
		ft_exiterror("ERROR : Fork error\n", 0);
	if (pid == 0)
	{
		dup2(outfilefd, 1);
		ft_execcmd(argv[arg], ncmd, envp);
	}
	waitpid(pid, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	int		outfilefd;
	int		infilefd;
	pid_t	pid;

	if (argc < 5)
		ft_exiterror("ERROR : Respect <infile cmd1 cmd2 ... outfile>\n", 0);
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		if (argc < 6)
			ft_exiterror(\
			"ERROR : Respect <here_doc LIMITER cmd1 cmd2 ... outfile>\n", 0);
		outfilefd = ft_open(argv[argc - 1], 2);
		ft_heredoc(argv[2], envp);
	}
	else
	{
		infilefd = ft_open(argv[1], 0);
		outfilefd = ft_open(argv[argc - 1], 1);
		dup2(infilefd, 0);
	}
	ft_nextcmd(argv, argc, outfilefd, envp);
	return (0);
}
