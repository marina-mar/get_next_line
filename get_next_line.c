/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 19:00:24 by mcouto            #+#    #+#             */
/*   Updated: 2019/05/23 22:24:42 by mcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int ft_isnotempty(char *buff)
{
	//check if theres smthng else in the string, if it has only "\0", then the read is over.
	if (*buff != '\0')
		return (1);
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
			if (ret == 0)
			{
				//define last line:
				if (ft_isnotempty(tmp) == 1)
				{
					//set i to size of tmp, so it copies all the string, then break to ft_organize:
					i = ft_strlen(tmp);
					break;
				}
				ft_strdel(line);
				return (0);
			}			
	//to deal with the '\n' being in the place of the old '\0':
			i = i - 1;
		}
		if (ret == -1)
			return (-1);
	   i++;	
	}
	ft_organize(&remain, &tmp, line, i);
	return (1);
}
/*
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
	printf("[%d]\n", get_next_line(fd, &hi));
	printf("%s", hi);
	printf("\n[%d]\n", get_next_line(fd, &hi));
	printf("%s", hi);
	printf("\n[%d]\n", get_next_line(fd, &hi));
	printf("%s", hi);
	printf("\n[%d]\n", get_next_line(fd, &hi));
	printf("%s", hi);
}
*/
