/*
** main.c
** 
** Made by Tatam
** Login   <tatam@protonmail.com>
** 
** Started on  Wed Sep 28 08:36:46 2016 Tatam
** Last update Wed Nov 22 18:41:03 2017 Tatam
*/
#include "lama.h"

int	main(int argc, char **argv)
{
  t_obj	*obj;
  int	i;

  obj = check_arg(argc, argv);
  obj->words = get_words(argv[3], obj);
  if (calcul_word(argv[0], obj) == 0)
    {
      fprintf(stderr, "Generation... ");
      for (i=obj->min; i<=obj->max; i++)
	mix(i, obj);
      free(obj->pt_function);
      free(obj->leet);
      free(obj->words);
      free(obj->options);
      free(obj);
      fprintf(stderr, "Done\n");
    }
  else
    fprintf(stderr, "Canceling.\n");
  
  return(0);
}
