/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 19:00:24 by mcouto            #+#    #+#             */
/*   Updated: 2019/05/30 21:52:05 by mcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

static int ft_lastlines(char **remain, char **line, int ret)
{
	int size;

	//check if theres smthng else in the string, if it has only "\0", then the read is over.
	//define last line:
	if (ret == -1)
		return (-1);
	if (**remain != '\0')
	{
		size = ft_strlen(*remain);
		*line = ft_strnew(size);
		*line = ft_strncpy(*line, *remain, (size));
		ft_strdel(remain);
		return (1);
	}
	*line = NULL;
	ft_strdel(remain);
	return (0);
}

static void	ft_organize(char **remain, char **line, int i)
{
	char *tmp;
	//this func was mostly to 25l rule of the norm, as a closure of the get_next_line, it
	//put all the stuff inside of the funcs
	tmp = *remain;
	*line = ft_strnew(i);
	*line = ft_strncpy(*line, *remain, (i));
	*remain = ft_strdup(&(*remain)[i + 1]);
	ft_strdel(&tmp);
}

static char	*ft_nonl(int *ret, char **remain, const int fd)
{
	//this func adds more volume to the "buff" when it reachs the end. It also
	//takes de position of "ret" so it changes in the original gnl if is -1 or 0;
	char *new;
	char *tmp;

	tmp = *remain;
	if(!(new = ft_strnew(BUFF_SIZE)))
		return (NULL);
	*ret = read(fd, new, BUFF_SIZE);
	if (!(*remain = ft_strjoin(*remain, new)))
		return (NULL);
	ft_strdel(&new);
	ft_strdel(&tmp);
	return (*remain);
}

int	get_next_line(const int fd, char **line)
{
	static char *remain;
	int i;
	int ret;

	ret = 0; //return from the read
	i = 0; //index to check '\n' char
	if (fd < 0 || !line)
		return (-1);
	if (remain == NULL) //first line mark, creates the remain string
		remain = ft_strnew(BUFF_SIZE);
				//leaking and can clean the remain used stuff already
	while (remain[i] != '\n')
	{
		if (remain[i] == '\0')
		{
			remain = ft_nonl(&ret, &remain, fd);
			if (ret < 1)
				return(ft_lastlines(&remain, line, ret));
	//to deal with the '\n' being in the place of the old '\0':
			i = i - 1;
		}
	   i++;
	}
	ft_organize(&remain, line, i);
	return (1);
}

/*int main(int ac, char **av)
{
	ac = 0;
	char *hi;
	int fd;
	int a;
	int ret;
	a = 0;
	ret = 0;
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
	 //error
	}
	while (a != 10)
	{
		ret = get_next_line(fd,&hi);
		printf("\n[%d]\n", ret);
		printf("%s", hi);
		a++;
	}
}*/
