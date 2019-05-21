/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 19:00:24 by mcouto            #+#    #+#             */
/*   Updated: 2019/05/20 20:18:04 by mcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//static ft_return(const int fd, char *buff)
//{
//	
//}
static char *ft_nonl(const int fd, char *buff)
{
	char *new;

	new = ft_strnew(BUFF_SIZE);
	if (read(fd, new, BUFF_SIZE) > 0)
		buff = ft_strjoin(buff, new);
	ft_strdel(&new);
	return (buff);
}

int get_next_line(const int fd, char **line)
{
	static char *remain;
	int i;
	char *tmp;

	i = 0;
	if (remain == NULL)
	{
		remain = ft_strnew(BUFF_SIZE);
		read(fd, remain, BUFF_SIZE);
	}
		tmp = remain;
	if (read(fd,remain,BUFF_SIZE) > 0)
		while (tmp[i] != '\n')
		{
			if (tmp[i] == '\0')
				tmp = ft_nonl(fd, tmp);
			i++;
		}
		*line = ft_strnew(i);
		*line = ft_strncpy(*line, tmp, (i));
		remain = ft_strdup(&tmp[i + 1]);
		ft_strdel(&tmp);
		return (1);
	}
	return (0);
}

int main(int ac, char **av)
{
	ac = 0;
	char *hi;
	int fd;

	fd = open(av[1], O_RDONLY);
	if (fd < 0) 
	{
	 //error
	}
	printf("%d\n", get_next_line(fd, &hi));
	printf("%s", hi);
	printf("\n%d\n", get_next_line(fd, &hi));
	printf("%s", hi);
	printf("\n%d\n", get_next_line(fd, &hi));
	printf("%s", hi);

}
