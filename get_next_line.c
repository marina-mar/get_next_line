/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 19:00:24 by mcouto            #+#    #+#             */
/*   Updated: 2019/05/29 04:04:49 by mcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

static int ft_lastlines(char **remain, char **lift, char **line, int ret)
{
	int size;

	size = ft_strlen(*lift);
	//check if theres smthng else in the string, if it has only "\0", then the read is over.
	//define last line:
	if (ret == -1)
		return (-1);
	if (**lift != '\0')
	{
		*line = ft_strnew(size);
		*line = ft_strncpy(*line, *lift, (size));
		*remain = NULL;
		return (1);
	}
	*line = NULL;
	return (0);
}

static void	ft_organize(char **remain, char **lift, char **line, int i)
{
	//this func was mostly to 25l rule of the norm, as a closure of the get_next_line, it 
	//put all the stuff inside of the funcs
	*line = ft_strnew(i);
	*line = ft_strncpy(*line, *lift, (i));
	*remain = ft_strdup(&(*lift)[i + 1]);
	ft_strdel(lift);
}

static char	*ft_nonl(int *ret, char *lift, const int fd)
{
	//this func adds more volume to the "buff" when it reachs the end. It also 
	//takes de position of "ret" so it changes in the original gnl if is -1 or 0;
	char *new;
	char *tmp;
	
	tmp = lift;
	if(!(new = ft_strnew(BUFF_SIZE)))
		return (NULL);
	*ret = read(fd, new, BUFF_SIZE);
	if (!(lift = ft_strjoin(lift, new)))
		return (NULL);
	ft_strdel(&new);
	if (*ret != 0)
		ft_strdel(&tmp);
	return (lift);	
}

int	get_next_line(const int fd, char **line)
{
	static char *remain;
	int i;
	int ret;
	char *lift;

	ret = 0; //return from the read
	i = 0; //index to check '\n' char
	if (fd < 0 || !line)
		return (-1);
	if (remain == NULL) //first line mark, creates the remain string
		remain = ft_strnew(BUFF_SIZE);
	lift = remain;//put it in tmp so we can avoid memory 
				//leaking and can clean the remain used stuff already
	while (lift[i] != '\n')
	{
		if (lift[i] == '\0')
		{
			lift = ft_nonl(&ret, lift, fd);
			if (ret < 1)
				return(ft_lastlines(&remain, &lift, line, ret));			
	//to deal with the '\n' being in the place of the old '\0':
			i = i - 1;
		}
	   i++;	
	}
	ft_organize(&remain, &lift, line, i);
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
		get_next_line(fd,&hi);
		printf("\n[%d]\n", ret);
		printf("%s", hi);
		a++;
	}
}*/
