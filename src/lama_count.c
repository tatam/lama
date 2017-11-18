/*
** lama_count.c
** 
** Made by Tatam
** Login   <tatam@protonmail.com>
** 
** Started on  Sat Nov 11 21:19:21 2017 Tatam
** Last update Sat Nov 18 11:58:35 2017 Tatam
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
	{
	  inter *= (obj->nb_words - j);
	}
      total += inter;
    }

  return(total);
}

long	count_first_maj(t_obj *obj, t_num *num)
{
  float	percent;
  float	inter;
  float	reste;
  long	total;
  int	maj;
  int	i;

  i = 0;
  maj = 0;
  while (obj->words[i])
    {
      if (obj->words[i][0] >= 'a' && obj->words[i][0] <= 'z')
	++maj;
      ++i;
    }
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
  long	perte;
  long	inter;
  long	total;
  int	no_maj;
  int	i;
  int	j;
  
  i = 0;
  no_maj = 0;  
  while (obj->words[i])
    {
      if (obj->words[i][0] <= 'a' || obj->words[i][0] >= 'z')
	++no_maj;
      ++i;
    }
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
  long	perte;
  long	inter;
  long	total;
  int	no_leet;
  int	leet;
  int	bool;
  int	c;
  int	i;
  int	j;
  int	l;

  i = 0;
  bool = 1;
  leet = 0;
  while (obj->words[i])
    {
      c = 0;
      while (obj->words[i][c])
	{
	  l = 0;
	  while (obj->leet[l])
	    {
	      if (obj->words[i][c] == obj->leet[l][0])
		{
		  bool = 0;
		  ++leet;
		  break;
		}
	      ++l;
	    }
	  if (bool == 0)
	    {
	      bool = 1;
	      break;
	    }
	  ++c;
	}
      ++i;
    }
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
