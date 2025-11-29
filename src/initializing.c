/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:28:35 by leramos-          #+#    #+#             */
/*   Updated: 2025/11/20 12:34:38 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*find_cmd_path(char **path_envp, char *cmd)
{
	char	*cmd_path;
	char	*tmp;
	int		i;

	i = 0;
	while (path_envp[i])
	{
		tmp = ft_strjoin(path_envp[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

static t_cmd	parse_single_cmd(char *cmd_str, t_pipex *data)
{
	t_cmd	cmd;

	if (!cmd_str || !*cmd_str)
		cleanup_and_exit(ERR_CMD_EMPTY, "Command is empty", data);
	cmd.args = NULL;
	cmd.path = NULL;
	cmd.args = ft_split(cmd_str, ' ');
	if (!cmd.args || !cmd.args[0] || !*cmd.args[0])
	{
		free_cmd(&cmd);
		cleanup_and_exit(ERR_ALLOC, "Error allocating data", data);
	}
	cmd.path = find_cmd_path(data->path_envp, cmd.args[0]);
	if (!cmd.path)
	{
		free_cmd(&cmd);
		cleanup_and_exit(ERR_CANT_FIND_CMD, "Couldn't find the command", data);
	}
	return (cmd);
}

void	parse_args(t_pipex *data, char **av, char **envp)
{
	data->path_envp = get_path_envp(envp);
	if (!data->path_envp)
		cleanup_and_exit(ERR_CANT_GET_PATH_ENVP, "Couldn't get Path ENVP", data);
	data->cmd1 = parse_single_cmd(av[2], data);
	data->cmd2 = parse_single_cmd(av[3], data);
}

void	open_files(t_pipex *data, char **av)
{
	data->in_fd = open(av[1], O_RDONLY);
	if (data->in_fd == -1)
		cleanup_and_exit(ERR_CANT_OPEN_IN, "Couldn't open input file.", data);
	data->out_fd = open(av[4], O_CREAT | O_WRONLY, 0644);
	if (data->out_fd == -1)
		cleanup_and_exit(ERR_CANT_OPEN_OUT, "Couldn't open output file.", data);
}

void	init_data(t_pipex *data)
{
	data->in_fd = -1;
	data->out_fd = -1;
	data->cmd1.args = NULL;
	data->cmd1.path = NULL;
	data->cmd2.args = NULL;
	data->cmd2.path = NULL;
	data->path_envp = NULL;
}
