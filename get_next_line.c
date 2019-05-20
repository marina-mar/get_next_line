/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 19:00:24 by mcouto            #+#    #+#             */
/*   Updated: 2019/05/19 19:32:36 by mcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int read_fd(const int fd)
{
	char *buff;
	char *new;
	int i;

	i = 0;
	buff == ft_strnew(BUFF_SIZE);
	read(fd, buff, BUFF_SIZE);
	while (buff[i] != '\n')
	{
		if (buff[i] == '\0')
		{
			new == ft_strnew(BUFF_SIZE);
			read(fd, new, BUFF_SIZE);
			buff = ft_strjoin(buff, new);
			free(new);
		}
		buff++;
	}
				
}

int get_next_line(const int fd, char **line)
{
	static char *remaind;
	int i;

}

/*int main(int ac, char **av)
{
char *hi;
	int fd;

	fd = open(av[1], O_RDONLY);
	if fd < 0 {
	 //error
	}
	get_next_line(fd, &hi);
}*/
