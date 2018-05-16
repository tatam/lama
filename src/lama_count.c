/*
** lama_count.c
** 
** Made by Tatam
** Login   <tatam@protonmail.com>
** 
** Started on  Sat Nov 11 21:19:21 2017 Tatam
** Last update Wed May 16 20:29:25 2018 Tatam
*/
#include "lama.h"

long	facto(int nb)
{
  if (nb == 1)
    return(nb);
  return(nb * facto(nb-1));
}

int	distri(int *array_coef, int *array_words, int nb_words, int p, int q)
{
  int	total;
  int	i;
  int	j;

  total = 0;
  for (i=1; i<=nb_words; i++)
    {
      for (j=0; j<=i; j++)
	array_coef[i-j] += array_words[i] * array_coef[i-j-1];
    }
  for (i=p; i<=q; i++)
    {
      if (i <= 0)
	total += 1;
      else
	total += facto(i) * array_coef[i];
    }
    
  return(total);
}

void	count_simple(t_obj *obj, t_num *num, t_len *len)
{
  int	*array_alias;
  int	*array_coef;
  int	*array_len;
  int	total;
  int	size;
  int	tmp;
  int	sum;
  int	i;
  int	j;

  total = 0;
  array_alias = init_array_alias_per_word(obj);
  array_coef = init_array_coef(obj);
  array_len = init_array_len_simple(obj);
  total = distri(array_coef, array_alias, obj->nb_words, obj->min, obj->max);
  
  size = 0;
  for (i=1; i<=obj->nb_words; i++)
    {
      tmp = array_alias[i];
      array_alias[i] = 0;
      free(array_coef);
      array_coef = init_array_coef(obj);
      distri(array_coef, array_alias, obj->nb_words, obj->min, obj->max);
      sum = 0;
      for (j=obj->min; j<=obj->max; j++)
	sum += facto(j) * array_coef[j-1];
      array_alias[i] = tmp;
      size += array_len[i] * sum;
    }

  num->nb_simple = total;
  len->len_simple = size + total;
  free(array_alias);
  free(array_coef);
}

long    count_first_maj(t_obj *obj, t_num *num)
{
  int	*array_unmatch;
  int	*array_alias;
  int	*array_coef;
  int	unmatch;
  int	total;
  int	tmp;
  int	k;

  unmatch = 0;
  array_unmatch = init_array_unmatch_first_maj(obj);
  array_alias = init_array_alias_per_word(obj);
  for (k=1; k<=obj->nb_words; k++)
    {
      total = 0;
      array_coef = init_array_coef(obj);
      tmp = array_alias[k];
      array_alias[k] = 0;
      total = distri(array_coef, array_alias, obj->nb_words, obj->min-1, obj->max-1);
      array_alias[k] = tmp;
      unmatch += array_unmatch[k] * total;
      free(array_coef);
    }
  
  free(array_unmatch);
  free(array_alias);
  
  return(num->nb_simple - unmatch);
}

long	count_all_maj(t_obj *obj, t_num *num)
{
  int	*array_unmatch;
  int	*array_coef;
  int	unmatch;
  int	total;

  total = 0;
  unmatch = 0;
  array_unmatch = init_array_unmatch_first_maj(obj);
  array_coef = init_array_coef(obj);
  unmatch = distri(array_coef, array_unmatch, obj->nb_words, obj->min, obj->max);
  total += num->nb_simple - unmatch;

  free(array_unmatch);
  free(array_coef);
  
  return(total);
}

long    count_leet(t_obj *obj, t_num *num)
{
  int	*array_unmatch;
  int	*array_coef;
  int	unmatch;
  int	total;

  total = 0;
  unmatch = 0;
  array_unmatch = init_array_unmatch_leet(obj);
  array_coef = init_array_coef(obj);  
  unmatch = distri(array_coef, array_unmatch, obj->nb_words, obj->min, obj->max);
  total += num->nb_simple - unmatch;
  free(array_unmatch);
  free(array_coef);
  
  return(total);
}
