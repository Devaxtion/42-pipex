/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:16:09 by leramos-          #+#    #+#             */
/*   Updated: 2025/12/02 16:09:55 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	print_to_stderr(const char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

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

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->args)
		free_str_array(cmd->args);
	if (cmd->path)
	{
		free(cmd->path);
		cmd->path = NULL;
	}
}

void	cleanup_and_exit(int status_code, const char *error_msg, t_pipex *data)
{
	if (data)
		;
	if (status_code != 0 && error_msg)
	{
		if (errno != 0)
		{
			perror(error_msg);
			exit(errno);
		}
		else
			print_to_stderr(error_msg);
	}
	exit(status_code);
}
