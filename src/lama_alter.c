/*
** lama_alter.c
** 
** Made by Tatam
** Login   <tatam@protonmail.com>
** 
** Started on  Sat Dec 16 12:24:09 2017 Tatam
** Last update Sat Dec 16 13:28:16 2017 Tatam
*/
#include "lama.h"

int	alter_first_maj(char *alter, char *simple)
{
  alter = strcpy(alter, simple);
  if (alter[0] >= 'a' && alter[0] <= 'z')
    {
      alter[0] -= 32;
      return(1);
    }
  return(0);
}

int	alter_leet(char *alter, char *simple, t_obj *obj)
{
  int	bool;
  int	c;
  int	l;

  c = 0;
  bool = 0;
  alter = strcpy(alter, simple);
  while (alter[c])
    {
      l = 0;
      while (obj->leet[l])
	{
	  if (alter[c] == obj->leet[l][0])
	    {
	      alter[c] = obj->leet[l][1];
	      bool = 1;
	      break;
	    }
	  ++l;
	}
      ++c;
    }
  
  return(bool);
}
