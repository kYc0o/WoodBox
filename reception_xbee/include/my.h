/*
** my.h for my.h in /home/alexis/WoodBox/reception_xbee/include
**
** Made by alexis
** Login   <alexis@epitech.net>
**
** Started on  Wed May 13 14:56:40 2015 alexis
** Last update Wed May 13 14:56:40 2015 alexis
*/

#ifndef MY_H_
# define MY_H_

int	my_strlenv2(char *str);
char	*my_strcat2(char *dest, char *src, int *j);
char	*file_blank(char *buffer);
char	*get_next_line(const int fd);
char	*my_strcpy(char *dest, char *src);
char	*time_file();
void	create_json(char *str);

#endif
