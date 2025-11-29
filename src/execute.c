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

static void	run_command(int in_fd, int out_fd, t_cmd cmd, char **path_envp)
{
	dup2(in_fd, FD_STDIN);
	dup2(out_fd, FD_STDOUT);
	close(in_fd);
	close(out_fd);
	execve(cmd.path, cmd.args, path_envp);
}

// Child 1 (pid1) - reads from input file, writes to pipe
// Child 2 (pid2) - reads from pipe, writes to output file
void	execute_pipex(t_pipex *data)
{
	int		pipefd[2];
	int		pid1;
	int		pid2;
	int		status1;
	int		status2;

	if (pipe(pipefd) == -1)
		cleanup_and_exit(ERR_PIPE_FAIL, "Pipe failed", data);
	pid1 = fork();
	pid2 = fork();
	if (pid1 == -1 || pid2 == -1)
		cleanup_and_exit(ERR_FORK_FAIL, "Fork failed", data);
	if (pid1 == 0)
	{
		close(pipefd[0]);
		run_command(data->in_fd, pipefd[1], data->cmd1, data->path_envp);
	}
	if (pid2 == 0)
	{
		close(pipefd[1]);
		run_command(pipefd[0], data->out_fd, data->cmd2, data->path_envp);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
}
