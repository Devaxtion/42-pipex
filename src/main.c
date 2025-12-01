/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:37:06 by leramos-          #+#    #+#             */
/*   Updated: 2025/12/01 16:54:23 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	data;
	int		status;

	if (ac != 5)
		cleanup_and_exit(ERR_INVALID_ARGS, "Use: infile c1 c2 outfile", NULL);
	init_data(&data, envp);
	open_files(&data, av);
	parse_args(&data, av);
	status = execute_pipex(&data);
	cleanup_and_exit(status, NULL, &data);
	return (0);
}
