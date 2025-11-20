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

	if (ac != 5)
		cleanup_and_exit(ERR_INVALID_ARGUMENTS, "Correct parameters: infile cmd1 cmd2 outfile", NULL);

	data.in_fd = open(av[1], O_RDONLY);
	if (data.in_fd == -1)
		cleanup_and_exit(ERR_CANT_OPEN_IN, "Couldn't open input file.", &data);

	data.out_fd = open(av[4], O_CREAT | O_WRONLY, 0644);
	if (data.out_fd == -1)
		cleanup_and_exit(ERR_CANT_OPEN_OUT, "Couldn't open output file.", &data);

	// parse cmds
	parse_cmds(&data, av, envp);

	print_array(data.cmd1.args, "cmd1");
	print_array(data.cmd2.args, "cmd2");

	execute_pipex(data, envp);

	return (0);
}