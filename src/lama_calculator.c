/*
** lama_calculator.c
** 
** Made by Tatam
** Login   <tatam@protonmail.com>
** 
** Started on  Sat Nov 11 21:19:21 2017 Tatam
** Last update Wed May 16 20:31:07 2018 Tatam
*/
#include "lama.h"

void	display_calcul(char *soft, t_num *num, t_obj *obj, t_len *len)
{
  int	i;
  int	h;

  i = 0;
  h = 1;
  while (obj->options[i])
    {
      if (obj->options[i] == 'h')
	  h = 0;
      ++i;
    }

  if (h == 0)
    {
      fprintf(stderr, "\n%s will generate %s words.\t(~%s)\n", soft, num->total, len->total);
      i = 0;
      while (obj->options[i])
	{
	  if (obj->options[i] == 'n')
	    fprintf(stderr, "  -n will generate %s words.\t(~%s)\n", num->simple, len->simple);
	  if (obj->options[i] == 'c')
	    fprintf(stderr, "  -c will generate %s words.\t(~%s)\n", num->first_maj, len->first_maj);
	  if (obj->options[i] == 'C')
	    fprintf(stderr, "  -C will generate %s words.\t(~%s)\n", num->all_maj, len->all_maj);
	  if (obj->options[i] == 'L')
	    fprintf(stderr, "  -L will generate %s words.\t(~%s)\n", num->leet, len->leet);
	  ++i;
	}
    }
  else
    {
      fprintf(stderr, "\n%s will generate %ld words.\t(~%ld)\n", soft, num->nb_total, len->len_total);
      i = 0;
      while (obj->options[i])
	{
	  if (obj->options[i] == 'n')
	    fprintf(stderr, "  -n will generate %ld words.\t(~%ld)\n", num->nb_simple, len->len_simple);
	  if (obj->options[i] == 'c')
	    fprintf(stderr, "  -c will generate %ld words.\t(~%ld)\n", num->nb_first_maj, len->len_first_maj);
	  if (obj->options[i] == 'C')
	    fprintf(stderr, "  -C will generate %ld words.\t(~%ld)\n", num->nb_all_maj, len->len_all_maj);
	  if (obj->options[i] == 'L')
	    fprintf(stderr, "  -L will generate %ld words.\t(~%ld)\n", num->nb_leet, len->len_leet);
	  ++i;
	}
    }
  fprintf(stderr, "\n");
}

int	calcul_word(char *soft, t_obj *obj)
{
  char	buff[SIZEMAX];  
  t_num	*num;
  t_len	*len;
  int	i;

  i = 0;
  num = safe_malloc(sizeof(t_num) + 1);
  len = safe_malloc(sizeof(t_len) + 1);
  num->nb_total = 0;
  len->len_total = 0;
  count_simple(obj, num, len);
  
  while (obj->options[i])
    {
      if (obj->options[i] == 'n')
	{
	  num->nb_total += num->nb_simple;
	  num->simple = human_nb_convert(num->nb_simple);
	  len->len_total += len->len_simple;
	  len->simple = human_len_convert(len->len_simple);
	}
      else if (obj->options[i] == 'c')
	{
	  num->nb_first_maj = count_first_maj(obj, num);
	  num->nb_total += num->nb_first_maj;
	  num->first_maj = human_nb_convert(num->nb_first_maj);
	  len->len_first_maj = len_first_maj(obj, len);
	  len->len_total += len->len_first_maj;
	  len->first_maj = human_len_convert(len->len_first_maj);
	}
      else if (obj->options[i] == 'C')
	{
	  num->nb_all_maj = count_all_maj(obj, num);
	  num->nb_total += num->nb_all_maj;
	  num->all_maj = human_nb_convert(num->nb_all_maj);
	  len->len_all_maj = len_all_maj(obj, len);
	  len->len_total += len->len_all_maj;
	  len->all_maj = human_len_convert(len->len_all_maj);
	}
      else if (obj->options[i] == 'L')
	{
	  num->nb_leet = count_leet(obj, num);
	  num->nb_total += num->nb_leet;
	  num->leet = human_nb_convert(num->nb_leet);
	  
	  len->len_leet = len_leet(obj, len);
	  len->len_total += len->len_leet;
	  len->leet = human_len_convert(len->len_leet);
	}
      ++i;
    }
  num->total = human_nb_convert(num->nb_total);
  len->total = human_len_convert(len->len_total);
  display_calcul(soft, num, obj, len);
  i = 0;
  while (obj->options[i])
    {
      if (obj->options[i] == 'n')
	{
	  free(num->simple);
	  free(len->simple);
	}
      else if (obj->options[i] == 'c')
	{
	  free(num->first_maj);
	}
      else if (obj->options[i] == 'C')
	{
	  free(num->all_maj);
	}
      else if (obj->options[i] == 'L')
	{
	  free(num->leet);
	}
      ++i;
    }  
  free(num);
  free(len);
  buff[0] = obj->res;
  while (buff[0] != 'y' && buff[0] != 'n')
    {
      fprintf(stderr, "Do you want to process ? [y/N] ");
      fgets(buff, SIZEMAX, stdin);
      if (buff[0] >= 'A' && buff[0] <= 'Z')
	buff[0] += 32;
      if (buff[0] == 10 || buff[0] == 32)
	buff[0] = 'n';
    }
  if (buff[0] == 'n')
    return(1);

  return(0);
}
