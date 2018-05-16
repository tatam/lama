/*
** lama_init_array.c
** 
** Made by Tatam
** Login   <tatam@protonmail.com>
** 
** Started on  Wed Apr 25 18:28:35 2018 Tatam
** Last update Wed Apr 25 18:28:36 2018 Tatam
*/
#include "lama.h"

int     *init_array_coef(t_obj *obj)
{
  int   *array_coef;
  int   i;

  array_coef = safe_malloc(sizeof(long) * obj->nb_words + 1);
  array_coef[0] = 1;
  for (i=1; i <= obj->nb_words+1; i++)
    array_coef[i] = 0;

  return(array_coef);
}

int     *init_array_alias_per_word(t_obj *obj)
{
  t_wd  *pt_words;
  int   *word_alias;
  int   i;

  pt_words = obj->list->first;
  word_alias = safe_malloc(sizeof(long) * obj->nb_words + 1);
  for (i = 0; i <= obj->nb_words+1; i++)
    word_alias[i] = 0;
  word_alias[0] = 1;
  i = 1;
  while (pt_words->next != NULL || pt_words->alias != NULL)
    {
      ++word_alias[i];
      if (pt_words->alias != NULL)
	pt_words = pt_words->alias;
      else if (pt_words->next != NULL)
	{
	  pt_words = pt_words->next;
	  ++i;
	}
    }
  ++word_alias[i];
  word_alias[i+1] = 0;

  return(word_alias);
}

int     *init_array_unmatch_leet(t_obj *obj)
{
  t_wd  *pt_words;
  int   *array_unmatch;
  int   bool;
  int   i;
  int   c;
  int   l;

  pt_words = obj->list->first;
  array_unmatch = safe_malloc(sizeof(long) * obj->nb_words + 1);
  for (i = 0; i <= obj->nb_words+1; i++)
    array_unmatch[i] = 0;
  i = 1;
  while (pt_words->next != NULL || pt_words->alias != NULL)
    {
      c = 0;
      bool = 0;
      while (pt_words->simple[c])
	{
	  l = 0;
	  while (obj->leet[l])
	    {
	      if (pt_words->simple[c] == obj->leet[l][0])
		{
		  bool = 1;
		  break;
		}
	      ++l;
	      if (bool == 1)
		break;
	    }
	  ++c;
	}
      if (bool == 0)
	++array_unmatch[i];
      if (pt_words->alias != NULL)
	pt_words = pt_words->alias;
      else if (pt_words->next != NULL)
	{
	  pt_words = pt_words->next;
	  ++i;
	}
    }
  c = 0;
  bool = 0;
  while (pt_words->simple[c])
    {
      l = 0;
      while (obj->leet[l])
	{
	  if (pt_words->simple[c] == obj->leet[l][0])
	    {
	      bool = 1;
	      break;
	    }
	  ++l;
	  if (bool == 1)
	    break;
	}
      ++c;
    }
  if (bool == 0)
    ++array_unmatch[i];

  return(array_unmatch);
}

int     *init_array_unmatch_first_maj(t_obj *obj)
{
  t_wd  *pt_words;
  int   *array_unmatch;
  int   i;

  pt_words = obj->list->first;
  array_unmatch = safe_malloc(sizeof(long) * obj->nb_words + 1);
  for (i = 0; i <= obj->nb_words+1; i++)
    array_unmatch[i] = 0;
  i = 1;
  while (pt_words->next != NULL || pt_words->alias != NULL)
    {
      if (pt_words->simple[0] < 'a' || pt_words->simple[0] > 'z')
	++array_unmatch[i];
      if (pt_words->alias != NULL)
	pt_words = pt_words->alias;
      else if (pt_words->next != NULL)
	{
	  pt_words = pt_words->next;
	  ++i;
	}
    }
  if (pt_words->simple[0] < 'a' || pt_words->simple[0] > 'z')
    ++array_unmatch[i];

  return(array_unmatch);
}

int     *init_array_len_simple(t_obj *obj)
{
  t_wd  *pt_words;
  int   *array_len;
  int   i;

  pt_words = obj->list->first;
  array_len = safe_malloc(sizeof(long) * obj->nb_words + 1);
  for (i=0; i <= obj->nb_words+1; i++)
    array_len[i] = 0;
  i = 1;
  while (pt_words->next != NULL || pt_words->alias != NULL)
    {
      array_len[i] += strlen(pt_words->simple);
      if (pt_words->alias != NULL)
	pt_words = pt_words->alias;
      else if (pt_words->next != NULL)
	{
	  pt_words = pt_words->next;
	  ++i;
	}
    }
  array_len[i] += strlen(pt_words->simple);

  return(array_len);
}

int     *init_array_len_first_maj(t_obj *obj)
{
  t_wd  *pt_words;
  int   *array_len;
  int   i;

  pt_words = obj->list->first;
  array_len = safe_malloc(sizeof(long) * obj->nb_words + 1);
  for (i=0; i <= obj->nb_words+1; i++)
    array_len[i] = 0;
  i = 1;
  while (pt_words->next != NULL || pt_words->alias != NULL)
    {
      if (pt_words->first_maj_status != 0)
	array_len[i] += strlen(pt_words->simple);
      if (pt_words->alias != NULL)
	pt_words = pt_words->alias;
      else if (pt_words->next != NULL)
	{
	  pt_words = pt_words->next;
	  ++i;
	}
    }
  if (pt_words->first_maj_status != 0)
    array_len[i] += strlen(pt_words->simple);

  return(array_len);
}
