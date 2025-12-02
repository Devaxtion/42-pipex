/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:36:38 by leramos-          #+#    #+#             */
/*   Updated: 2025/12/02 17:12:28 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_cmd_path(char *cmd, char **path_envp)
{
	char	*cmd_path;
	char	*tmp;
	int		i;

	if (!cmd || !*cmd)
		return (NULL);
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

static char	**parse_cmd_args(char *cmd_str)
{
	char	**cmd_args;

	cmd_args = ft_split(cmd_str, ' ');
	if (!cmd_args)
		return (NULL);
	return (cmd_args);
}

static char	*parse_cmd_path(char *cmd, char **envp)
{
	char	*cmd_path;
	char	**path_envp;

	path_envp = get_path_envp(envp);
	if (!path_envp)
		return (NULL);
	cmd_path = get_cmd_path(cmd, path_envp);
	free_str_array(path_envp);
	path_envp = NULL;
	if (!cmd_path)
		return (NULL);
	return (cmd_path);
}

void	parse_single_cmd(char *cmd_str, t_cmd *cmd, t_pipex *data)
{
	if (!cmd_str || !*cmd_str)
		return ;
	cmd->args = parse_cmd_args(cmd_str);
	if (cmd->args == NULL)
		return ;
	cmd->path = parse_cmd_path(cmd->args[0], data->envp);
	if (cmd->path == NULL)
		return ;
}
