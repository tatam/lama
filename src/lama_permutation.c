/*
** permutation.c
** 
** Made by Tatam
** Login   <tatam@protonmail.com>
** 
** Started on  Mon Oct  3 09:45:07 2016 Tatam
** Last update Sun Dec 17 10:14:26 2017 Tatam
*/
#include "lama.h"

void	swap(t_wd *pt_words1, t_wd *pt_words2)
{
  t_wd	tmp;

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
	  swap(obj->pt_words[obj->cur_perm], obj->pt_words[i]);
	  obj->cur_perm++;
	  permutation(obj);
	  obj->cur_perm--;
	  swap(obj->pt_words[obj->cur_perm], obj->pt_words[i]);
	}
    }
}

void	rwhile(int curr_while, t_obj *obj)
{
  int	bool;

  bool = 0;
  while (obj->pt_words[curr_while]->next != NULL && bool == 0)
    {
      if (curr_while != obj->interval-1)
	{
	  obj->pt_words[curr_while+1] = obj->pt_words[curr_while]->next;
	  rwhile(curr_while+1, obj);
	  if (obj->pt_words[curr_while]->next == obj->pt_words[curr_while+1])
	    bool = 1;
	  else
	    obj->pt_words[curr_while] = obj->pt_words[curr_while]->next;
	}
      else
	{
	  obj->cur_perm = 0;
	  permutation(obj);
	  obj->pt_words[curr_while] = obj->pt_words[curr_while]->next;
	}
    }
  if (bool == 0)
    {
      obj->cur_perm = 0;
      permutation(obj);
    }
}

void	mix(int interval, t_obj *obj)
{
  int	curr_while;

  curr_while = 0;
  obj->pt_words = safe_malloc(interval * sizeof(t_wd*) + 1);
  obj->pt_words[0] = obj->list->first;
  obj->interval = interval;
  rwhile(curr_while, obj);
  free(obj->pt_words);
}
