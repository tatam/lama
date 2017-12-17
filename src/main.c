/*
** main.c
** 
** Made by Tatam
** Login   <tatam@protonmail.com>
** 
** Started on  Wed Sep 28 08:36:46 2016 Tatam
** Last update Sun Dec 17 13:23:47 2017 Tatam
*/
#include "lama.h"

int	main(int argc, char **argv)
{
  t_obj	*obj;
  int	i;

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
