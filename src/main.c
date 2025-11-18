/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:37:06 by leramos-          #+#    #+#             */
/*   Updated: 2025/11/18 14:31:18 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	char	**infile;
	char	**outfile;
	char	**cmd1;
	char	**cmd2;
	int		in;
	int		out;
	int		pipefd[2];
	int		pid;

	// open input file
	in = open(infile, O_RDONLY);
	// if it doesn't exist, exit, can't continue
	if (in == -1)
		;

	// open output file
	out = open(outfile, O_WRONLY);
	// if it doesn't exist, create a new one and open it
	if (out == -1)
		;

	// create a child process
	pid = fork();

	// create a pipe
	pipe(pipefd);

	// get the commands
	// ex: ["grep", "a", NULL];
	cmd1 = ft_split(av[2], " ");
	cmd2 = ft_split(av[3], " ");

	// get PATH
	// 		itterate in envp array till i find a string that starts with "PATH="
	//		they are separated by :
	;
	// find the absolute path of cmd1 and cmd2

	// child process
	if (pid == 0)
	{
		// close unused write end of pipe
		close(pipefd[1]);

		// replace std input with read end of pipe
		dup2(pipefd[0], 0);

		// execute cmd2
		;

		// pass the output to output file
		;
	}
	// parent process
	else
	{
		// close unused read end of pipe
		close(pipefd[0]);

		// replace std output with write end of pipe
		dup2(pipefd[1], 1);

		// execute cmd1 and pass the output to the input of cmd2
		;
	}

	// wait till child process finishes
	waitpid(pid);

	return (0);
}