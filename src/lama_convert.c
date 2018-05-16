/*
** lama_convert.c
** 
** Made by Tatam
** Login   <tatam@protonmail.com>
** 
** Started on  Sat Nov 11 21:19:21 2017 Tatam
** Last update Sat Apr  7 20:46:18 2018 Tatam
*/
#include "lama.h"

char	*human_nb_convert(long nb)
{
  char	*human;
  long	copy;
  int	rest;
  int	wlen;
  int	len;
  int	p;
  int	i;

  len = 1;
  copy = nb;
  while (copy >= 10)
    {
      copy /= 10;
      ++len;
    }
  wlen = len;
  if (len >= 3)
    wlen += len / 3;
  if (len % 3 == 0)
    --wlen;
  human = safe_malloc(wlen * sizeof(char) + 1);
  human[wlen] = '\0';
  copy = nb;
  p = 0;
  for (i=wlen-1; i>=0; i--)
    {
      if (p == 3)
	{
	  human[i] = ' ';
	  p = 0;
	  --i;
	}
      rest = copy % 10;
      copy = copy / 10;
      human[i] = rest + '0';
      ++p;
    } 

  return(human);
}

char	*human_len_convert(long nb)
{
  float	fnb;
  char	*unit[] = {"o", "K", "M", "G", "T", "P", "?", '\0'};
  char	*human;
  int	len_unit;
  int	copy;
  int	rest;
  int	len;
  int	dnb;
  int	u;
  int	i;

  u = 0;
  len_unit = 0;
  fnb = (float)nb;
  while (unit[u++])
      ++len_unit;
  u = 0;
  while (fnb >= 1024.0)
    {
      fnb /= 1024.0;
      ++u;
    }
  if (u > len_unit)
      u = len_unit;
  dnb = (int)fnb;
  if ((float)fnb - (float)dnb >= 0.5)
    ++fnb;  
  nb = (int)fnb;
  len = 0;  
  copy = nb;
  while (copy >= 10)
    {
      copy /= 10;
      ++len;
    }
  human = safe_malloc(len * sizeof(char) + 2);
  human[len+2] = '\0';
  human[len+1] = *unit[u];
  copy = nb;
  for (i=len; i>=0; i--)
    {
      rest = copy % 10;
      copy = copy / 10;
      human[i] = rest + '0';
    }

  return(human);
}
