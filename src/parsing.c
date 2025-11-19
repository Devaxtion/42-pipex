/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:28:35 by leramos-          #+#    #+#             */
/*   Updated: 2025/11/19 15:13:15 by leramos-         ###   ########.fr       */
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

void	parse_cmds(t_pipex *data, char **av, char **envp)
{
	char	**path_envp;

	path_envp = get_path_envp(envp);
	
	// av[2] == "grep main"
	// av[3] == "wc -l"

	// 1. transform av[i] to ft_split(av[i], ' ')
	// cmd1 = ["grep", "main"]
	// cmd2 = ["wc", "-l"]
	data->cmd1.args = ft_split(av[2], ' ');
	data->cmd2.args = ft_split(av[3], ' ');

	// 2. find path of cmd[0]
	data->cmd1.path = find_cmd_path(path_envp, data->cmd1.args[0]);
	data->cmd2.path = find_cmd_path(path_envp, data->cmd1.args[0]);

	// 3. replace cmd[0] with the found path (freeing first cmd[0])
	// cmd1 = ["usr/bin/grep", "main"]
	// cmd2 = ["usr/bin/wc", "-l"]
	free(data->cmd1.args[0]);
	free(data->cmd2.args[0]);
	data->cmd1.args[0] = data->cmd1.path;
	data->cmd2.args[0] = data->cmd2.path;
}
