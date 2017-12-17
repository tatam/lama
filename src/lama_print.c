/*
** lama_print.c
** 
** Made by Tatam
** Login   <tatam@protonmail.com>
** 
** Started on  Tue Oct  4 11:51:32 2016 Tatam
** Last update Sun Dec 17 10:33:04 2017 Tatam
*/
#include "lama.h"

void	print_simple(t_obj *obj)
{
  int	i;

  for (i=0; i<obj->interval; i++)
    fprintf(stdout, "%s", obj->pt_words[i]->simple);
  fprintf(stdout, "\n");
}

void	print_first_maj(t_obj *obj)
{
  int	i;

  if (obj->pt_words[0]->first_maj_status != 0)
    {
      fprintf(stdout, "%s", obj->pt_words[0]->first_maj);
      for (i=1; i<obj->interval; i++)
	fprintf(stdout, "%s", obj->pt_words[i]->simple);
      fprintf(stdout, "\n");
    }
}

void	print_all_maj(t_obj *obj)
{
  int	status;
  int	i;
  
  status = 0;
  for (i=0; i<obj->interval; i++)
    status += obj->pt_words[i]->first_maj_status;
  if (status != 0)
    {
      for (i=0; i<obj->interval; i++)
	fprintf(stdout, "%s", obj->pt_words[i]->first_maj);
      fprintf(stdout, "\n");
    }
}

void	print_leet(t_obj *obj)
{
  int	status;
  int	i;

  status = 0;
  for (i=0; i<obj->interval; i++)
    status += obj->pt_words[i]->leet_status;
  if (status != 0)
    {
      for (i=0; i<obj->interval; i++)
	fprintf(stdout, "%s", obj->pt_words[i]->leet);
      fprintf(stdout, "\n");
    }
}
