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
	close(unused_fd);
	dup2(in_fd, FD_STDIN);
	dup2(out_fd, FD_STDOUT);
	execve(cmd.path, cmd.args, envp);
}

void	execute_pipex(t_pipex data, char **envp)
{
	int		pipefd[2];
	int		pid;

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
		run_command(pipefd[0], data.out_fd, pipefd[1], data.cmd2, envp);
	else
		run_command(data.in_fd, pipefd[1], pipefd[0], data.cmd1, envp);
}
