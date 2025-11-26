/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:37:06 by leramos-          #+#    #+#             */
/*   Updated: 2025/11/20 12:46:45 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// ./pipex infile cmd1 cmd2 outfile
int	main(int ac, char **av, char **envp)
{
	t_pipex	data;

	init_files(&data, ac, av);
	parse_cmds(&data, av, envp);
	execute_pipex(data, envp);
	return (0);
}