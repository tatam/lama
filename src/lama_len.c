/*
** lama_len.c
** 
** Made by Tatam
** Login   <tatam@protonmail.com>
** 
** Started on  Sat Nov 11 21:19:21 2017 Tatam
** Last update Sat Nov 18 12:01:53 2017 Tatam
*/
#include "lama.h"

int     len_words(t_obj *obj)
{
  int   len;
  int	i;

  i = 0;
  len = 0;
  while (obj->words[i])
    {
      len += strlen(obj->words[i]) + 1;
      ++i;
    }

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
  float percent;
  float inter;
  float reste;
  long  total;
  int   maj;
  int   i;

  i = 0;
  maj = 0;
  while (obj->words[i])
    {
      if (obj->words[i][0] >= 'a' && obj->words[i][0] <= 'z')
	++maj;
      ++i;
    }
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
  long  perte;
  long  inter;
  long  total;
  int   no_maj;
  int   i;
  int   j;

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
      inter *= (len->avg_len * j - (i));
      perte += inter;
    }
  total = len->len_simple - perte;
  
  return(total);
}

long	len_leet(t_obj *obj, t_len *len)
{
  long  perte;
  long  inter;
  long  total;
  int   no_leet;
  int   leet;
  int   bool;
  int   c;
  int   i;
  int   j;
  int   l;

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
