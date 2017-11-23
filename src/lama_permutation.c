/*
** permutation.c
** 
** Made by Tatam
** Login   <tatam@protonmail.com>
** 
** Started on  Mon Oct  3 09:45:07 2016 Tatam
** Last update Thu Nov 23 20:33:30 2017 Tatam
*/
#include "lama.h"

void	swap(int *pt_words1, int *pt_words2)
{
  int	tmp;

  tmp = *pt_words1;
  *pt_words1 = *pt_words2;
  *pt_words2 = tmp;
}

void	permutation(t_obj *obj)
{
  int	i;
  int	c;

  if (obj->cur_perm == obj->interval-1)
    {
      c = 0;
      while(obj->pt_function[c] != NULL)
	{
	  obj->pt_function[c](obj);
	  c++;
	}
    }
  else
    {
      for(i=obj->cur_perm; i<obj->interval; ++i)
	{
	  swap(&obj->pt_words[obj->cur_perm], &obj->pt_words[i]);
	  obj->cur_perm++;
	  permutation(obj);
	  obj->cur_perm--;
	  swap(&obj->pt_words[obj->cur_perm], &obj->pt_words[i]);
	}
    }
}

void	forfor(int value, int curr_for, t_obj *obj)
{
  int	i;

  obj->pt_words[curr_for] = value;
  for (i=value; i<=(obj->nb_words - (obj->interval - curr_for)); i++)
    {
      if (curr_for != obj->interval-1)
	{
	  value++;
	  forfor(value, curr_for+1, obj);
	  obj->pt_words[curr_for] = value;
	}
      else
	{
	  obj->pt_words[curr_for] = i;
	  obj->cur_perm = 0;
	  permutation(obj);
	}
    }
}

void	mix(int interval, t_obj *obj)
{
  int	curr_for;

  curr_for = 0;
  obj->pt_words = safe_malloc(interval * sizeof(int*) + 1);
  obj->interval = interval;
  forfor(0, curr_for, obj);
  free(obj->pt_words);
}
