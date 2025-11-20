/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
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

static t_cmd	parse_single_cmd(char *cmd_str, char **path_envp)
{
	t_cmd	cmd;

	cmd.args = ft_split(cmd_str, ' ');
	cmd.path = find_cmd_path(path_envp, cmd.args[0]);
	free(cmd.args[0]);
	cmd.args[0] = cmd.path;
	return (cmd);
}

void	parse_cmds(t_pipex *data, char **av, char **envp)
{
	char	**path_envp;

	path_envp = get_path_envp(envp);
	if (!path_envp)
		return ;
	data->cmd1 = parse_single_cmd(av[2], path_envp);
	data->cmd2 = parse_single_cmd(av[3], path_envp);
	free(path_envp);
}
