/*
** lama_arg.c
** 
** Made by Tatam
** Login   <tatam@protonmail.com>
** 
** Started on  Wed Sep 28 09:08:08 2016 Tatam
** Last update Sat Nov 18 11:55:12 2017 Tatam
*/
#include "lama.h"

void	usage(char **argv)
{
  fprintf(stderr, "Usage:\n");
  fprintf(stderr, "\t%s [min] [max] [file] [Options]\n", argv[0]);
  fprintf(stderr, "Option:\n");
  fprintf(stderr, "\t-h\tDisplay output informations as Human readable format.\n");
  fprintf(stderr, "\t-n\tPrint without transfomation.\n");
  fprintf(stderr, "\t-c\tPrint with first letter caitalized.\n");
  fprintf(stderr, "\t-C\tPrint with first letter caitalized of each words.\n");
  fprintf(stderr, "\t-L\tPrint with leet speak transformation.\n");
  fprintf(stderr, "\t-S\tAdd specials charaters to the words list.\n");
  fprintf(stderr, "\t-N\tAdd numeric sequences to the words list.\n");
  fprintf(stderr, "\t-y\tForce the answer to 'y' (yes) before the passwords generation.\n");
  fprintf(stderr, "Example:\n");
  fprintf(stderr, "\tlama 2 5 wordlist.lst -n -c -C > dictionnary.lst\n");
  fprintf(stderr, "\tlama 1 4 wordlist.lst -LS -h > dictionnary.lst\n");
  fprintf(stderr, "\tlama 1 2 wordlist.lst -nyh > dictionnary.lst\n");
  fprintf(stderr, "More help:\n");
  fprintf(stderr, "\tman %s\n\n", argv[0]);

  exit(2);
}

void	integer_error(char **argv)
{
  fprintf(stderr, "Error:\n");
  fprintf(stderr, "\tmin and max values must be integers.\n");
  fprintf(stderr, "\tmin and max values must be between 1 and 9.\n");
  fprintf(stderr, "\tmin value must be egal or lower than max value.\n");
  fprintf(stderr, "\n");
  usage(argv);
}

void	u_sort(char *options)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  while (options[i])
    {
      j = i + 1;
      while (options[j])
	{
	  if (options[j] == options[i])
	    options[j] = '0';
	  ++j;
	}
      ++i;
    }
  i = 0;
  j = 0;
  while(options[i])
    {
      j= i + 1;
      while (options[j])
	{
	  if (options[i] == '0' && options[j] != '0')
	    {
	      options[i] = options[j];
	      options[j] = '0';
	    }
	  ++j;
	}
      ++i;
    }
  i = 0;
  while (options[i])
    {
      if (options[i] == '0')
	options[i] = '\0';
      ++i;
    }
}

char	*get_opt(char **argv)
{
  char	*options;
  int	nb_opt;
  int	i;
  int	j;
  int	k;

  k = 0;
  i = 4;
  while (argv[i])
    {
      j = 0;
      while (argv[i][j])
	{
	  if (argv[i][j] != '-')
	    ++nb_opt;
	  ++j;
	}
      ++i;
    }
  options = safe_malloc(nb_opt * sizeof(char*) + 1);
  i = 4;
  while (argv[i])
    {
      j = 0;
      while (argv[i][j])
	{
	  if (argv[i][j] != '-')
	    {
	      options[k] = argv[i][j];
	      ++k;
	    }
	  ++j;
	}
      ++i;
    }
  options[k] = '\0';
  u_sort(options);

  return(options);
}

char	**get_leet()
{
  FILE	*file;
  char	**leet;
  char	word[SIZEMAX];
  int	nb_words;
  int	i;

  i = 0;
  file = safe_ropen(LEET_FILE);
  nb_words = count_words(file);
  leet = safe_malloc(nb_words * sizeof(char*) + 1);
  while (fgets(word, SIZEMAX, file) != NULL)
    {
      if (word[1] == '=')
	{
	  leet[i] = safe_malloc(2 * sizeof(char) + 1);
	  leet[i][0] = word[0];
	  leet[i][1] = word[2];
	  ++i;
	}
    }
  leet[i] = NULL;
  fclose(file);

  return(leet);
}

t_obj	*check_arg(int argc, char **argv)
{
  t_obj	*obj;
  int	i;
  int	o;

  i = 0;
  o = -1;
  if (argc < 5)
    usage(argv);
  obj = safe_malloc(sizeof(t_obj) + 1);
  obj->pt_function = safe_malloc(1024);
  sscanf (argv[1], "%d", &obj->min);
  sscanf (argv[2], "%d", &obj->max);
  if (obj->min < 1 || obj->max < 1 || obj->min > 9 || obj->max > 9 || obj->min > obj->max)
    integer_error(argv);
  obj->options = get_opt(argv);
  obj->res = '0';
  while (obj->options[i])
    {
      if (obj->options[i] == 'n')
	obj->pt_function[++o] = &print_simple;
      else if (obj->options[i] == 'c')
	obj->pt_function[++o] = &print_first_maj;
      else if (obj->options[i] == 'C')
	obj->pt_function[++o] = &print_all_maj;
      else if (obj->options[i] == 'L')
	{
	  obj->pt_function[++o] = &print_leet;
	  obj->leet = get_leet();
	}
      else if (obj->options[i] == 'y')
	obj->res = 'y';
      else if (obj->options[i] != 'S' &&
	       obj->options[i] != 'N' &&
	       obj->options[i] != 'h')
	{
	  fprintf(stderr, "%s: Option -%c unknown.\n", argv[0], obj->options[i]);
	  usage(argv);
	}
      i++;
    }
  obj->pt_function[++o] = NULL;

  return(obj);
}
