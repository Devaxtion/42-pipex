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

static void	run_command(int in_fd, int out_fd, int unused_fd, t_cmd cmd, char **path_envp)
{
	close(unused_fd);
	dup2(in_fd, FD_STDIN);
	dup2(out_fd, FD_STDOUT);
	close(in_fd);
	close(out_fd);
	execve(cmd.path, cmd.args, path_envp);
}

void	execute_pipex(t_pipex *data)
{
	int		pipefd[2];
	int		pid1;
	int		pid2;
	int		status;

	if (pipe(pipefd) == -1)
		cleanup_and_exit(1, "Pipe failed", data);
	pid1 = fork();
	if (pid1 == 0)
		run_command(pipefd[0], data->out_fd, pipefd[1], data->cmd2, data->path_envp);
	pid2 = fork();
	if (pid2 == 0)
		run_command(data->in_fd, pipefd[1], pipefd[0], data->cmd1, data->path_envp);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
}
