/*
** permutation.c
** 
** Made by Tatam
** Login   <tatam@protonmail.com>
** 
** Started on  Mon Oct  3 09:45:07 2016 Tatam
** Last update Sat Nov 11 21:08:27 2017 Tatam
*/
#include "lama.h"

void	swap(int *pt_words1, int *pt_words2)
{
  int	tmp;

  tmp = *pt_words1;
  *pt_words1 = *pt_words2;
  *pt_words2 = tmp;
}

void	permutation(int curr, int interval, t_obj *obj)
{
  int	i;
  int	c;

  if (curr == interval-1)
    {
      c = 0;
      while(obj->pt_function[c] != NULL)
	{
	  obj->pt_function[c](interval, obj);
	  c++;
	}
    }
  else
    {
      for(i=curr; i<interval; ++i)
	{
	  swap(&obj->pt_words[curr], &obj->pt_words[i]);
	  permutation(curr+1, interval, obj);
	  swap(&obj->pt_words[curr], &obj->pt_words[i]);
	}
    }
}

void	forfor(int value, int curr_pos, int interval, t_obj *obj)
{
  int	i;

  obj->pt_words[curr_pos] = value;
  for (i=value; i<=(obj->nb_words - (interval - curr_pos)); i++)
    {
      if (curr_pos != interval-1)
	{
	  value++;
	  forfor(value, curr_pos+1, interval, obj);
	  obj->pt_words[curr_pos] = value;
	}
      else
	{
	  obj->pt_words[curr_pos] = i;
	  permutation(0, interval, obj);
	}
    }
}

void	mix(int interval, t_obj *obj)
{
  int	curr_pos;

  curr_pos = 0;
  obj->pt_words = safe_malloc(interval * sizeof(int*) + 1);
  forfor(0, curr_pos, interval, obj);
  free(obj->pt_words);
}
