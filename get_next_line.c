/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 19:00:24 by mcouto            #+#    #+#             */
/*   Updated: 2019/05/22 05:14:10 by mcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//static void ft_lastline()

static void	ft_lastline(char **line)
{
	ft_strdel(line);
}



static void	ft_organize(char **remain, char **tmp, char **line, int i)
{
	*line = ft_strnew(i);
	*line = ft_strncpy(*line, *tmp, (i));
	*remain = ft_strdup(&(*tmp)[i + 1]);
	ft_strdel(tmp);
}

static char	*ft_nonl(int *ret, char *buff, const int fd)
{
	char *new;
	char *tmp;
	
	tmp = buff;
	new = ft_strnew(BUFF_SIZE);
	if ((*ret = read(fd, new, BUFF_SIZE)) > 0)
		buff = ft_strjoin(buff, new);
	ft_strdel(&new);
	ft_strdel(&tmp);
	return (buff);	
}

int	get_next_line(const int fd, char **line)
{
	static char *remain;
	int i;
	int ret;
	char *tmp;

	ret = 0;
	i = 0;
	if (fd < 0 || !line)
		return (-1);
	if (remain == NULL)
		remain = ft_strnew(BUFF_SIZE);
	tmp = remain;
	while (tmp[i] != '\n')
	{
		if (tmp[i] == '\0')
		{
			tmp = ft_nonl(&ret, tmp, fd);
//to deal with the '\n' being in the place of the old '\0':
			i = i - 1;

			if (ret == 0)
			{
				ft_lastline(line);
				return (0);
			}
		}
		if (ret == -1)
			return (-1);
	   i++;	
	}
	ft_organize(&remain, &tmp, line, i);
	return (1);
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
	printf("\n%d\n", get_next_line(fd, &hi));
	printf("%s", hi);
}
