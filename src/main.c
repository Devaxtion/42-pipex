/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:37:06 by leramos-          #+#    #+#             */
/*   Updated: 2025/11/19 15:11:34 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// ./pipex infile cmd1 cmd2 outfile
int	main(int ac, char **av, char **envp)
{
	t_pipex	data;
	// int		pipefd[2];
	// int		pid;

	if (ac != 5)
		cleanup_and_exit(ERR_INVALID_ARGUMENTS, "Correct parameters: infile cmd1 cmd2 outfile", NULL);

	data.in_fd = open(av[1], O_RDONLY);
	if (data.in_fd == -1)
		cleanup_and_exit(ERR_CANT_OPEN_IN, "Couldn't open input file.", &data);

	data.out_fd = open(av[4], O_CREAT | O_WRONLY, 0644);
	if (data.out_fd == -1)
		cleanup_and_exit(ERR_CANT_OPEN_OUT, "Couldn't open output file.", &data);

	// parse cmds
	parse_cmds(&data, av, envp);

	print_array(data.cmd1.args, "cmd1");
	print_array(data.cmd2.args, "cmd2");








	
	// create a child process
	// pid = fork();

	// create a pipe
	// pipe(pipefd);

	// child process
	// if (pid == 0)
	// {
	// 	// close unused write end of pipe
	// 	close(pipefd[1]);

	// 	// replace std input with read end of pipe
	// 	dup2(pipefd[0], 0);

	// 	// execute cmd2
	// 	;

	// 	// pass the output to output file
	// 	;
	// }
	// // parent process
	// else
	// {
	// 	// close unused read end of pipe
	// 	close(pipefd[0]);

	// 	// replace std output with write end of pipe
	// 	dup2(pipefd[1], 1);

	// 	// execute cmd1 and pass the output to the input of cmd2
	// 	;
	// }

	// wait till child process finishes
	// waitpid(pid);

	return (0);
}