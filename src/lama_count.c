/*
** lama_count.c
** 
** Made by Tatam
** Login   <tatam@protonmail.com>
** 
** Started on  Sat Nov 11 21:19:21 2017 Tatam
** Last update Sun Dec 17 11:41:11 2017 Tatam
*/
#include "lama.h"

long	count_simple(t_obj *obj)
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
      total += inter;
    }

  return(total);
}

long	count_first_maj(t_obj *obj, t_num *num)
{
  t_wd	*word;
  float	percent;
  float	inter;
  float	reste;
  long	total;
  int	maj;

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
  inter = num->nb_simple * percent / 100;
  total = inter;
  reste = inter - total;
  if (reste >= 0.5)
    ++total; // Is this line work ?
  
  return(total);
}

long	count_all_maj(t_obj *obj, t_num *num)
{
  t_wd	*word;
  long	perte;
  long	inter;
  long	total;
  int	no_maj;
  int	i;
  int	j;
  
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
      perte += inter;
    }
  total = num->nb_simple - perte;

  return(total);
}

long	count_leet(t_obj *obj, t_num *num)
{
  t_wd	*word;
  long	perte;
  long	inter;
  long	total;
  int	no_leet;
  int	leet;
  int	i;
  int	j;

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
      perte += inter;
    }
  total = num->nb_simple - perte;
  
  return(total);
}

t_num	*count_init(t_obj *obj)
{
  t_num	*num;

  num = safe_malloc(sizeof(t_num) + 1);
  num->nb_simple = count_simple(obj);
  num->nb_total = 0;

  return(num);
}
