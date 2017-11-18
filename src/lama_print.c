/*
** lama_print.c
** 
** Made by Tatam
** Login   <tatam@protonmail.com>
** 
** Started on  Tue Oct  4 11:51:32 2016 Tatam
** Last update Sat Nov 18 12:04:32 2017 Tatam
*/
#include "lama.h"

void	print_simple(int interval, t_obj *obj)
{
  int	i;

  for (i=0; i<interval; i++)
    printf("%s", obj->words[obj->pt_words[i]]);
  printf("\n");
}

void	print_first_maj(int interval, t_obj *obj)
{
  int	i;

  if (obj->words[obj->pt_words[0]][0] >= 'a' && obj->words[obj->pt_words[0]][0] <= 'z')
    {
      for (i=0; i<interval; i++)
	{
	  if (i == 0)
	    {
	      obj->words[obj->pt_words[0]][0] -= 32;
      	      printf("%s", obj->words[obj->pt_words[i]]);
	      obj->words[obj->pt_words[0]][0] += 32;	      
	    }
	  else
	    printf("%s", obj->words[obj->pt_words[i]]);
	}
      printf("\n");
    }
}

void	print_all_maj(int interval, t_obj *obj)
{
  int	bool;
  int	i;
  
  // Update 2017-02-03
  // Do not print if no caracteres
  bool = 1;
  for (i=0; i<interval; i++)
    {
      if (obj->words[obj->pt_words[i]][0] >= 'a' && obj->words[obj->pt_words[i]][0] <= 'z')
	{
	  bool = 0;
	  i = interval;
	}
    }
  // End update

  if (bool == 0)
    {
      for (i=0; i<interval; i++)
	{
	  if (obj->words[obj->pt_words[i]][0] >= 'a' && obj->words[obj->pt_words[i]][0] <= 'z')
	    {
	      obj->words[obj->pt_words[i]][0] -= 32;
      	      printf("%s", obj->words[obj->pt_words[i]]);
	      obj->words[obj->pt_words[i]][0] += 32;
	    }
	  else
	    printf("%s", obj->words[obj->pt_words[i]]);
	}
      printf("\n");
    }
}

void	print_leet(int interval, t_obj *obj)
{
  char  *tmp_word;
  int	bool;
  int   i;
  int	c;
  int	l;

  bool = 1;
  for (i=0; i<interval; i++)
    {
      c = 0;
      while (obj->words[obj->pt_words[i]][c])
	{
	  l = 0;
	  while (obj->leet[l])
	    {
	      if (obj->words[obj->pt_words[i]][c] == obj->leet[l][0])
		{
		  bool = 0;
		  i = interval;
		  break;
		}
	      ++l;
	    }
	  if (bool == 0)
	    break;
	  ++c;
	}
    }
  if (bool == 0)
    {
      for (i=0; i<interval; i++)
	{
	  tmp_word = safe_malloc(strlen(obj->words[obj->pt_words[i]]) + 1);
	  tmp_word = strcpy(tmp_word, obj->words[obj->pt_words[i]]);
	  c = 0;
	  while (tmp_word[c])
	    {
	      l = 0;
	      while (obj->leet[l])
		{
		  if (tmp_word[c] == obj->leet[l][0])
		    {
		      tmp_word[c] = obj->leet[l][1];
		      break;
		    }
		  ++l;
		}
	      ++c;
	    }
	  printf("%s", tmp_word);
	  free(tmp_word);
	}
      printf("\n");
    }
}
