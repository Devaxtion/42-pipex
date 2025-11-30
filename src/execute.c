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

static void	run_command(int in_fd, int out_fd, t_cmd cmd, t_pipex *data)
{
	dup2(in_fd, FD_STDIN);
	dup2(out_fd, FD_STDOUT);
	close(in_fd);
	close(out_fd);
	execve(cmd.path, cmd.args, data->path_envp);
	cleanup_and_exit(ERR_EXECVE_FAIL, "Execve failed", data);
}

static int	create_fork(t_pipex *data)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		cleanup_and_exit(ERR_FORK_FAIL, "Fork failed", data);
	return (pid);
}

// Child 1 (pid1) - reads from input file, writes to pipe
// Child 2 (pid2) - reads from pipe, writes to output file
int	execute_pipex(t_pipex *data)
{
	int		pipefd[2];
	int		pid1;
	int		pid2;
	int		status1;
	int		status2;
	int		exit_status;

	if (pipe(pipefd) == -1)
		cleanup_and_exit(ERR_PIPE_FAIL, "Pipe failed", data);
	pid1 = create_fork(data);
	if (pid1 == 0)
	{
		close(pipefd[0]);
		if (data->in_fd == -1)
			data->in_fd = open("/dev/null", O_RDONLY);
		run_command(data->in_fd, pipefd[1], data->cmd1, data);
	}
	pid2 = create_fork(data);
	if (pid2 == 0)
	{
		close(pipefd[1]);
		if (data->out_fd == -1)
			cleanup_and_exit(ERR_NO_PERMS, NULL, data);
		run_command(pipefd[0], data->out_fd, data->cmd2, data);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);

	if (WIFEXITED(status2))
		exit_status = WEXITSTATUS(status2);
	else if (pid1 != -1 && WIFEXITED(status1))
		exit_status = WEXITSTATUS(status1);
	else
		exit_status = 0;
	return (exit_status);
}
