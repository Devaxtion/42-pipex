/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:29:48 by leramos-          #+#    #+#             */
/*   Updated: 2025/12/02 16:07:43 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipe(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
}

char	**get_path_envp(char **envp)
{
	char	*path;
	int		path_idx;

	path_idx = find_prefix_in_array(envp, "PATH=");
	if (path_idx == -1)
		return (NULL);
	path = envp[path_idx] + 5;
	return (ft_split(path, ':'));
}

static int	does_str_start_with(char *str, char *prefix)
{
	int	i;

	i = 0;
	while (str[i] && prefix[i])
	{
		if (str[i] != prefix[i])
			return (0);
		i++;
	}
	return (1);
}

int	find_prefix_in_array(char **array, char *prefix)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (does_str_start_with(array[i], prefix))
			return (i);
		i++;
	}
	return (-1);
}

int	find_word_in_array(char	**array, char *word)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (ft_strnstr(array[i], word, ft_strlen(array[i])) != NULL)
			return (i);
		i++;
	}
	return (-1);
}
