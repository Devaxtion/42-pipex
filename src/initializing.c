/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:28:35 by leramos-          #+#    #+#             */
/*   Updated: 2025/12/01 16:55:53 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parse_args(t_pipex *data, char **av)
{
	parse_single_cmd(av[2], &data->cmd1, data);
	if (data->cmd1.args == NULL || data->cmd1.path == NULL)
	{
		free_cmd(&data->cmd1);
		parse_fake_cmd(&data->cmd1, data);
	}
	parse_single_cmd(av[3], &data->cmd2, data);
	ft_printf("THIS IS AV %s and THIS IS CMD %s\n", av[3], data->cmd2.args[0]);
	if (data->cmd2.args == NULL || data->cmd2.path == NULL)
		cleanup_and_exit(ERR_CANT_FIND_CMD, "Couldn't find the command", data);
}

void	open_files(t_pipex *data, char **av)
{
	data->in_fd = open(av[1], O_RDONLY);
	if (data->in_fd == -1)
		ft_printf("%s: No such file or directory\n", av[1]);
	data->out_fd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->out_fd == -1)
		ft_printf("%s: Permission denied\n", av[4]);
}

void	init_data(t_pipex *data, char **envp)
{
	data->in_fd = -1;
	data->out_fd = -1;
	data->cmd1.args = NULL;
	data->cmd1.path = NULL;
	data->cmd2.args = NULL;
	data->cmd2.path = NULL;
	data->envp = envp;
}
