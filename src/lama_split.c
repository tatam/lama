/*
** lama_split.c
** 
** Made by Tatam
** Login   <tatam@protonmail.com>
** 
** Started on  Sun Jan 14 11:02:44 2018 Tatam
** Last update Sun Jan 14 15:27:35 2018 Tatam
*/
#include "lama.h"

int	count_split(char *word)
{
  int	nb_word;
  int	i;

  i = 0;
  nb_word = 1;
  while (word[i])
    {
      if (word[i] == '|'  && word[i-1] != '\\')
	++nb_word;
      ++i;
    }

  return(nb_word);
}

int	cut_word(char *dst, char *src, int *s)
{
  int	d;

  d = 0;
  while (src[*s] != '\n')
    {
      if ( (s != 0 && src[*s] == '|') || (src[*s] == '|' && src[*s+1] != '\0') )
	{
	  ++*s;
	  dst[d] = '\0';
	  return(-1);
	}
      else if (src[*s] == '\\' && src[*s+1] == '|')
	{	  
	  dst[d] = '|';
	  *s += 2;
	  ++d;
	}
      else
	{
	  dst[d] = src[*s];
	  ++*s;
	  ++d;
	}
    }
  dst[d] = '\0';
  
  return(0);
}

char	**split_pipe(char *word)
{
  char  **words;
  int   nb_word;
  int	begin;
  int	i;

  begin = 0;
  nb_word = count_split(word);
  words = safe_malloc(nb_word * sizeof(char*) + 1);
  for (i=0; i<nb_word; i++)
    {
      words[i] = safe_malloc(SIZEMAX);
      cut_word(words[i], word, &begin);
      if (strlen(words[i]) == 0)
	{
	  --nb_word;
	  --i;
	}
    }
  words[i] = '\0';

  if (words[0] != '\0')
    return(words);
  return(NULL);
}
