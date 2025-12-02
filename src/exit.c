/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:16:09 by leramos-          #+#    #+#             */
/*   Updated: 2025/12/02 17:12:27 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	print_to_stderr(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
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

void	cleanup_and_exit(int status_code, char *error_msg)
{
	if (status_code != 0 && error_msg)
	{
		if (status_code == 127)
		{
			print_to_stderr("Command not found");
			exit(status_code);
		}
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
