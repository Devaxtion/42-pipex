/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:43:29 by leramos-          #+#    #+#             */
/*   Updated: 2025/12/02 17:12:29 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_command(int in_fd, int out_fd, t_cmd cmd, t_pipex *data)
{
	dup2(in_fd, FD_STDIN);
	dup2(out_fd, FD_STDOUT);
	close(in_fd);
	close(out_fd);
	execve(cmd.path, cmd.args, data->envp);
	cleanup_and_exit(ERR_EXECVE_FAIL, "Execve failed");
}

int	get_exit_status(int primary_status, int fallback_status)
{
	if (WIFEXITED(primary_status))
		return (WEXITSTATUS(primary_status));
	if (WIFEXITED(fallback_status))
		return (WEXITSTATUS(fallback_status));
	return (0);
}
