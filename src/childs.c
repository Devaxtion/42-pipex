/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:02:15 by leramos-          #+#    #+#             */
/*   Updated: 2025/12/02 16:20:11 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	create_first_child(t_pipex *data, int *pipefd)
{
	int		pid;
	int		infile;
	t_cmd	cmd;

	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		infile = open(data->av[1], O_RDONLY);
		if (infile == -1)
		{
			close(pipefd[1]);
			cleanup_and_exit(ERR_CANT_OPEN_IN, data->av[1], data);
		}
		parse_single_cmd(data->av[2], &cmd, data);
		if (cmd.args == NULL || cmd.path == NULL)
		{
			free_cmd(&cmd);
			cleanup_and_exit(ERR_CANT_FIND_CMD, "Can't find the cmd", data);
		}
		run_command(infile, pipefd[1], cmd, data);
	}
	return (pid);
}

static int	create_second_child(t_pipex *data, int *pipefd)
{
	int		pid;
	int		outfile;
	t_cmd	cmd;

	pid = fork();
	if (pid == 0)
	{
		close(pipefd[1]);
		outfile = open(data->av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (outfile == -1)
		{
			close(pipefd[0]);
			cleanup_and_exit(ERR_NO_PERMS, NULL, data);
		}
		parse_single_cmd(data->av[3], &cmd, data);
		if (cmd.args == NULL || cmd.path == NULL)
		{
			free_cmd(&cmd);
			cleanup_and_exit(ERR_CANT_FIND_CMD, "Can't find the cmd", data);
		}
		run_command(pipefd[0], outfile, cmd, data);
	}
	return (pid);
}

// Child 1 (pids[0]) - reads from input file, writes to pipe
// Child 2 (pids[1]) - reads from pipe, writes to output file
void	create_childs(t_pipex *data)
{
	data->pids[0] = create_first_child(data, data->pipefd);
	if (data->pids[0] == -1)
		cleanup_and_exit(ERR_FORK_FAIL, "Fork 1 failed", data);
	data->pids[1] = create_second_child(data, data->pipefd);
	if (data->pids[1] == -1)
		cleanup_and_exit(ERR_FORK_FAIL, "Fork 2 failed", data);
}

void	wait_for_childs(int pids[2], int status[2])
{
	waitpid(pids[0], &status[0], 0);
	waitpid(pids[1], &status[1], 0);
}
