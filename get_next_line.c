/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 19:00:24 by mcouto            #+#    #+#             */
/*   Updated: 2019/05/28 17:15:22 by mcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

static int ft_lastlines(char **remain, char **tmp, char **line, int ret)
{
	int size;

	size = ft_strlen(*tmp);
	//check if theres smthng else in the string, if it has only "\0", then the read is over.
	//define last line:
	if (ret == -1)
		return (-1);
	if (**tmp != '\0')
	{
		*line = ft_strnew(size);
		*line = ft_strncpy(*line, *tmp, (size));
		if (remain)
			ft_strdel(remain);
		return (1);
	}
	*line = NULL;
	return (0);
}

static void	ft_organize(char **remain, char **tmp, char **line, int i)
{
	//this func was mostly to 25l rule of the norm, as a closure of the get_next_line, it 
	//put all the stuff inside of the funcs
	*line = ft_strnew(i);
	*line = ft_strncpy(*line, *tmp, (i));
	*remain = ft_strdup(&(*tmp)[i + 1]);
	ft_strdel(tmp);
}

static char	*ft_nonl(int *ret, char *buff, const int fd)
{
	//this func adds more volume to the "buff" when it reachs the end. It also 
	//takes de position of "ret" so it changes in the original gnl if is -1 or 0;
	char *new;
	char *tmp;
	
	tmp = buff;
	if(!(new = ft_strnew(BUFF_SIZE)))
		return (NULL);
	*ret = read(fd, new, BUFF_SIZE);
	if(!(buff = ft_strjoin(buff, new)))
		return (NULL);
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

	ret = 0; //return from the read
	i = 0; //index to check '\n' char
	if (fd < 0 || !line)
		return (-1);
	if (remain == NULL) //first line mark, creates the remain string
		remain = ft_strnew(BUFF_SIZE);
	tmp = remain;//put it in tmp so we can avoid memory 
				//leaking and can clean the remain used stuff already
	while (tmp[i] != '\n')
	{
		if (tmp[i] == '\0')
		{
			tmp = ft_nonl(&ret, tmp, fd);
			if (ret < 1)
				return(ft_lastlines(&remain, &tmp, line, ret));			
	//to deal with the '\n' being in the place of the old '\0':
			i = i - 1;
		}
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
	int a;
	a = 7;
	fd = open(av[1], O_RDONLY);
	if (fd < 0) 
	{
	 //error
	}
	while (a != 0)
	{
		a = get_next_line(fd,&hi);
		printf("\n[%d]\n", a);
		printf("%s", hi);
	}
}
