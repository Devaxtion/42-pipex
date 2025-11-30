/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:16:09 by leramos-          #+#    #+#             */
/*   Updated: 2025/11/19 15:13:09 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_str_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static void	free_fd(int fd)
{
	if (fd > 0)
		close(fd);
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->args)
	{
		free_str_array(cmd->args);
		cmd->args = NULL;
	}
	if (cmd->path)
	{
		free(cmd->path);
		cmd->path = NULL;
	}
}

static void	free_data(t_pipex *data)
{
	if (data->in_fd)
		free_fd(data->in_fd);
	if (data->out_fd)
		free_fd(data->out_fd);
	free_cmd(&data->cmd1);
	free_cmd(&data->cmd2);
	if (data->path_envp)
	{
		free_str_array(data->path_envp);
		data->path_envp = NULL;
	}
}

void	cleanup_and_exit(int status_code, const char *error_msg, t_pipex *data)
{
	if (data)
		free_data(data);
	if (status_code != 0)
	{
		ft_printf("Error\n");
		if (error_msg)
			ft_printf("%s\n", error_msg);
	}
	exit(status_code);
}
