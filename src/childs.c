/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:02:15 by leramos-          #+#    #+#             */
/*   Updated: 2025/12/02 17:49:18 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	create_first_child(t_pipex *data, int *pipefd, t_cmd cmd)
{
	int		pid;
	int		infile;

	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		infile = open(data->av[1], O_RDONLY);
		if (infile == -1)
		{
			close(pipefd[1]);
			perror("");
			cleanup_and_exit(ERR_CANT_OPEN_IN, data->av[1]);
		}
		parse_single_cmd(data->av[2], &cmd, data);
		if (cmd.args == NULL || cmd.path == NULL)
		{
			close(infile);
			close(pipefd[1]);
			free_cmd(&cmd);
			cleanup_and_exit(ERR_CANT_FIND_CMD, "Command not found");
		}
		run_command(infile, pipefd[1], cmd, data);
	}
	return (pid);
}

static int	create_second_child(t_pipex *data, int *pipefd, t_cmd cmd)
{
	int		pid;
	int		outfile;

	pid = fork();
	if (pid == 0)
	{
		close(pipefd[1]);
		outfile = open(data->av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (outfile == -1)
		{
			close(pipefd[0]);
			perror("");
			cleanup_and_exit(ERR_CANT_OPEN_OUT, NULL);
		}
		parse_single_cmd(data->av[3], &cmd, data);
		if (cmd.args == NULL || cmd.path == NULL)
		{
			close(outfile);
			close(pipefd[0]);
			free_cmd(&cmd);
			cleanup_and_exit(ERR_CANT_FIND_CMD, "Command not found");
		}
		run_command(pipefd[0], outfile, cmd, data);
	}
	return (pid);
}

// Child 1 (pids[0]) - reads from input file, writes to pipe
// Child 2 (pids[1]) - reads from pipe, writes to output file
void	create_childs(t_pipex *data)
{
	t_cmd	cmd;

	cmd.path = NULL;
	cmd.args = NULL;
	data->pids[0] = create_first_child(data, data->pipefd, cmd);
	if (data->pids[0] == -1)
		cleanup_and_exit(ERR_FORK_FAIL, "Fork 1 failed");
	data->pids[1] = create_second_child(data, data->pipefd, cmd);
	if (data->pids[1] == -1)
		cleanup_and_exit(ERR_FORK_FAIL, "Fork 2 failed");
}

void	wait_for_childs(int pids[2], int status[2])
{
	int	i;
	int	temp_pid;
	int	temp_status;

	status[0] = 0;
	status[1] = 0;
	i = 0;
	while (i < 2)
	{
		temp_pid = waitpid(-1, &temp_status, 0);
		if (temp_pid == -1)
			continue ;
		if (temp_pid == pids[0])
			status[0] = temp_status;
		else if (temp_pid == pids[1])
			status[1] = temp_status;
		i++;
	}
}
