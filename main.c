/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumontei <mumontei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 21:13:32 by mumontei          #+#    #+#             */
/*   Updated: 2022/06/28 04:00:38 by mumontei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int		fd;
	char	*line;
	int		i;

	//fd = open("./gnlTester/files/41_with_nl:", O_RDONLY);
	fd = open("theaetetus_by_plato.txt", O_RDONLY);
	i = 0;
	while (i < 10)
	{
		line = get_next_line(fd);
		printf("line [%02d]: %s\n", i, line);
		i++;
		free(line);
	}
	close(fd);
}
