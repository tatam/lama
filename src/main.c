/*
** main.c
** 
** Made by Tatam
** Login   <tatam@protonmail.com>
** 
** Started on  Wed Sep 28 08:36:46 2016 Tatam
** Last update Tue Apr 10 20:25:55 2018 Tatam
*/
#include "lama.h"

int	main(int argc, char **argv)
{
  t_obj	*obj;
  char	*buff;
  int	buff_size;
  int	i;

  // Get the L3 cache size and set the buffer
  buff_size = get_L3_cache();
  buff = safe_malloc(buff_size);
  setbuffer(stdout, buff, buff_size);

  obj = check_arg(argc, argv);
  obj->list = get_words_list(argv[3], obj);
  if (calcul_word(argv[0], obj) == 0)
    {
      fprintf(stderr, "Generation... ");
      for (i=obj->min; i<=obj->max; i++)
	mix(i, obj);
      free(obj->pt_function);
      free(obj->leet);
      free(obj->list);
      free(obj->options);
      free(obj);
      fflush(stdout);
      fprintf(stderr, "Done\n");
    }
  else
    fprintf(stderr, "Canceling.\n");
  
  return(0);
}
