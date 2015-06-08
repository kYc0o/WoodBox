/*
** port_found.c for portfound in /home/alexis/mainson_mix
**
** Made by alexis
** Login   <alexis@epitech.net>
**
** Started on  Fri Mar 27 16:22:40 2015 alexis
** Last update Fri Mar 27 16:22:40 2015 alexis
*/

#include <stdio.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "my.h"

char buffer[1024];
FILE	*json_data;

char  *time_file()
{
    time_t temps = time(0);

    strftime(buffer, sizeof buffer, "%FT%H:%M:%SZ", localtime(&temps));
    return (buffer);
}

void	create_json(char *str)
{
  int	i;

  printf("%s\n", str);
  json_data = fopen("data.json", "a");
  if (json_data)
    {
      fprintf(json_data, "%s", str);
      i = 0;
      if (str[i] == '[')
	{
	  fprintf(json_data, "{", str);
	  i++;
	}
      if (fclose(json_data))
	printf("Error json_data close\n");
    }
  else
    printf("json_data fail\n");
}

void	main()
{
  int	fd;
  char	*str;
  int i = 0;
  int flag = 0;

  fd = open("/dev/ttyUSB0", O_RDWR);
  json_data = fopen("data.json", "a");
  fprintf(json_data, "[{\n\"Date\" : \"%s\",", time_file());
  fclose(json_data);
  dup2(fd, 0);
  while ((str = get_next_line(0)) != NULL)
    {
      if (!(flag))
	{
	  while ((str = get_next_line(0)) != NULL)
	    {
	      create_json(str);
	    }
	  flag = 1;
	}
      else
	{
	  while ((str = get_next_line(0)) != NULL)
	    {
	      json_data = fopen("data.json", "a");
	      if (json_data)
		{
		  fprintf(json_data, ",%s\n", str);
		  if (fclose(json_data))
		    printf("Error json_data close\n");
		}
	      else
		printf("json_data fail\n");
	    }
	}
    }
  close (fd);
  exit (0);
}
