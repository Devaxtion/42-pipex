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

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
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
	
	cmd.args = NULL;
	cmd.path = NULL;
	if (!cmd_str || !*cmd_str)
		return (cmd);
	cmd.args = ft_split(cmd_str, ' ');
	if (!cmd.args || !cmd.args[0] || !*cmd.args[0])
	{
		free_str_array(cmd.args);
		return (cmd);
	}
	cmd.path = find_cmd_path(data->path_envp, cmd.args[0]);
	if (!cmd.path)
		free_str_array(cmd.args);
	return (cmd);
}

static t_cmd	parse_fake_cmd(t_pipex *data)
{
	t_cmd	cmd;

	cmd.args = ft_split("false", ' ');
	cmd.path = ft_strdup("/usr/bin/false");
	if (!cmd.args || !cmd.path)
		cleanup_and_exit(ERR_ALLOC, "Memory allocation failed", data);
	return (cmd);
}

void	parse_args(t_pipex *data, char **av, char **envp)
{
	data->path_envp = get_path_envp(envp);
	if (!data->path_envp)
		cleanup_and_exit(ERR_CANT_GET_PATH_ENVP, "Couldn't get paths", data);
	data->cmd1 = parse_single_cmd(av[2], data);
	if (!data->cmd1.path || !data->cmd1.args)
		data->cmd1 = parse_fake_cmd(data);
	data->cmd2 = parse_single_cmd(av[3], data);
	if (!data->cmd2.path || !data->cmd2.args)
		cleanup_and_exit(ERR_CANT_FIND_CMD, "Couldn't find the command", data);
}

void	open_files(t_pipex *data, char **av)
{
	data->in_fd = open(av[1], O_RDONLY);
	if (data->in_fd == -1)
		ft_printf("%s: No such file or directory\n", av[1]);
	data->out_fd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->out_fd == -1)
	{
		ft_printf("%s: Permission denied\n", av[4]);
		// cleanup_and_exit(ERR_NO_PERMS, NULL, data);
	}
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
