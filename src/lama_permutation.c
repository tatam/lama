/*
** permutation.c
** 
** Made by Tatam
** Login   <tatam@protonmail.com>
** 
** Started on  Mon Oct  3 09:45:07 2016 Tatam
** Last update Thu Jan 18 21:26:03 2018 Tatam
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

t_wd	*move_word(t_wd *word)
{
  if (word->alias != NULL)
    word = word->alias;
  else
    word = word->next;

  return(word);
}

t_wd	*last_alias(t_wd *word)
{
  t_wd	*curr;

  curr = word;
  while (curr->alias != NULL)
    curr = curr->alias;

  return(curr);
}

void	rwhile(int curr_while, t_obj *obj)
{
  int	bool;

  bool = 0;
  //  while (obj->pt_words[curr_while]->next != NULL && bool == 0)
  while ( (obj->pt_words[curr_while]->next != NULL ||
	   obj->pt_words[curr_while]->alias != NULL) && bool == 0)
    {
      if (curr_while != obj->interval-1)
	{
	  obj->pt_words[curr_while+1] = obj->pt_words[curr_while]->next;
	  rwhile(curr_while+1, obj);
	  if (last_alias(obj->pt_words[curr_while]->next) == obj->pt_words[curr_while+1] &&
	      obj->pt_words[curr_while]->alias == NULL) // WORK
	    bool = 1;
	  else
	    obj->pt_words[curr_while] = move_word(obj->pt_words[curr_while]);
	}
      else
	{
	  obj->cur_perm = 0;
	  permutation(obj);
	  obj->pt_words[curr_while] = move_word(obj->pt_words[curr_while]);
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
