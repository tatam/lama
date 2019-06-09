/*
** lama_builtin.c
** 
** Made by Tatam
** Login   <tatam@protonmail.com>
** 
** Started on  Sat Nov 11 09:45:20 2017 Tatam
** Last update Sat Nov 18 11:54:01 2017 Tatam
*/
#include "lama.h"

FILE	*safe_ropen(char *file_name)
{
  FILE	*file;
  
  file = fopen(file_name, "r");
  if (file == NULL)
    {
      fprintf(stderr, "Fail to open %s file: %s\n", file_name, strerror(errno));
      exit(EXIT_FAILURE);
    }

  return(file);
}

void	*safe_malloc(int value)
{
  void	*thing;

  thing = malloc(value);
  if (thing == NULL)
    {
      fprintf(stderr, "Fail to process malloc: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }

  return(thing);
}

int	get_L3_cache()
{
  FILE	*fd;
  char	name1[256];
  char	name2[256];
  char	delimiter[256];
  char	value[256];

  fd = safe_ropen("/proc/cpuinfo");
  while (!feof(fd))
    {
      fscanf(fd, "%s %s %s %s", name1, name2, delimiter, value);
      if (strcmp(name1, "cache") == 0 && strcmp(name2, "size") == 0)
	{
	  fclose(fd);
	  return(atoi(value) * 1024);
	}
    }
  fclose(fd);

  // return 4M by default
  return(4194304);
}
