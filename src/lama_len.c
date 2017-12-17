/*
** lama_len.c
** 
** Made by Tatam
** Login   <tatam@protonmail.com>
** 
** Started on  Sat Nov 11 21:19:21 2017 Tatam
** Last update Sun Dec 17 11:40:57 2017 Tatam
*/
#include "lama.h"

int     len_words(t_obj *obj)
{
  t_wd	*word;
  int   len;

  len = 0;
  word = safe_malloc(sizeof(t_wd*) + 1);
  word = obj->list->first;
  while (word->next != NULL)
    {
      len += strlen(word->simple) + 1;
      word = word->next;
    }
  len += strlen(word->simple) + 1;
  
  return(len);
}

long	len_simple(t_obj *obj, t_len *len)
{
  long	total;
  long	inter;
  int	i;
  int	j;

  total = 0;
  for(i=obj->min-1; i<obj->max; i++)
    {
      inter = 1;
      for(j=0; j<=i; j++)
	  inter *= (obj->nb_words - j);
      inter *= (len->avg_len * j - (i));
      total += inter;
    }

  return(total);  
}

long	len_first_maj(t_obj *obj, t_len *len)
{
  t_wd	*word;
  float percent;
  float inter;
  float reste;
  long  total;
  int   maj;

  maj = 0;
  word = safe_malloc(sizeof(t_wd*) + 1);
  word = obj->list->first;
  while (word->next != NULL)
    {
      maj += word->first_maj_status;
      word = word->next;
    }
  maj += word->first_maj_status;
  percent = (float)maj * 100.0 / (float)obj->nb_words;
  inter = len->len_simple * percent / 100.0;
  total = inter;
  reste = inter - total;
  if (reste >= 0.5)
    ++total; // Is this line work ?
  
  return(total);
}

long	len_all_maj(t_obj *obj, t_len *len)
{
  t_wd	*word;
  long  perte;
  long  inter;
  long  total;
  int   no_maj;
  int   i;
  int   j;

  no_maj = 0;
  word = safe_malloc(sizeof(t_wd*) + 1);
  word = obj->list->first;
  while (word->next != NULL)
    {
      if (word->first_maj_status == 0)
	++no_maj;
      word = word->next;
    }
  if (word->first_maj_status == 0)
    ++no_maj;
  perte = 0;
  for(i=obj->min-1; i<obj->max; i++)
    {
      inter = 1;
      for(j=0; j<=i; j++)
	inter *= (no_maj - j);
      inter *= (len->avg_len * j - (i));
      perte += inter;
    }
  total = len->len_simple - perte;
  
  return(total);
}

long	len_leet(t_obj *obj, t_len *len)
{
  t_wd	*word;
  long  perte;
  long  inter;
  long  total;
  int   no_leet;
  int   leet;
  int   i;
  int   j;

  leet = 0;
  word = safe_malloc(sizeof(t_wd*) + 1);
  word = obj->list->first;
  while (word->next != NULL)
    {
      leet += word->leet_status;
      word = word->next;
    }
  leet += word->leet_status;
  no_leet = obj->nb_words - leet;
  perte = 0;
  for(i=obj->min-1; i<obj->max; i++)
    {
      inter = 1;
      for(j=0; j<=i; j++)
	inter *= (no_leet - j);
      inter *= (len->avg_len * j - (i));
      perte += inter;
    }
  total = len->len_simple - perte;
  
  return(total);
}

t_len	*len_init(t_obj *obj)
{
  t_len	*len;

  len = safe_malloc(sizeof(t_len) + 1);
  len->len_words = len_words(obj);
  len->avg_len = (float)len->len_words / (float)obj->nb_words;
  len->len_simple = len_simple(obj, len);
  len->len_total = 0;

  return(len);
}
