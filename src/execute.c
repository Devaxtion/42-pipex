/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:43:29 by leramos-          #+#    #+#             */
/*   Updated: 2025/11/20 13:57:39 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	run_command(int in_fd, int out_fd, int unused_fd, t_cmd cmd, char **envp)
{
	close(unused_fd);             // close unused pipe end
	dup2(in_fd, FD_STDIN);        // redirect stdin
	dup2(out_fd, FD_STDOUT);      // redirect stdout
	execve(cmd.path, cmd.args, envp);
}


void	execute_pipex(t_pipex data, char **envp)
{
	int		pipefd[2];
	int		pid;

	// create a pipe
	pipe(pipefd);

	// create a child process
	pid = fork();

	if (pid == 0)	// child process
		run_command(pipefd[0], data.out_fd, pipefd[1], data.cmd2, envp);
	else 			// parent process
		run_command(data.in_fd, pipefd[1], pipefd[0], data.cmd1, envp);
}
