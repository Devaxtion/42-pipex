/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:37:06 by leramos-          #+#    #+#             */
/*   Updated: 2025/12/02 16:21:42 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_data(t_pipex *data, char **av, char **envp)
{
	data->av = av;
	data->envp = envp;
	if (pipe(data->pipefd) == -1)
		cleanup_and_exit(ERR_PIPE_FAIL, "Pipe failed", data);
	data->pstatus[0] = 0;
	data->pstatus[1] = 0;
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	data;
	int		exit_status;

	if (ac != 5)
		cleanup_and_exit(ERR_INVALID_ARGS, "Use: infile c1 c2 outfile", NULL);
	init_data(&data, av, envp);
	create_childs(&data);
	close_pipe(data.pipefd);
	wait_for_childs(data.pids, data.pstatus);
	exit_status = get_exit_status(data.pstatus[1], data.pstatus[0]);
	cleanup_and_exit(exit_status, NULL, &data);
	return (0);
}
