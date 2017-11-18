/*
** lama_file.c
** 
** Made by Tatam
** Login   <tatam@protonmail.com>
** 
** Started on  Wed Sep 28 08:38:46 2016 Tatam
** Last update Tue Nov 14 21:39:17 2017 Tatam
*/
#include "lama.h"

int	count_words(FILE *file)
{
  char  word[SIZEMAX];
  int	nb;

  nb = 0;
  while (fgets(word, SIZEMAX, file) != NULL)
    ++nb;
  rewind(file);
  
  return(nb);
}

void	count_all_words(char *file_name, t_obj *obj)
{
  FILE  *file;
  int	nb_words;
  int	i;

  i = 0;
  nb_words = 0;
  file = safe_ropen(file_name);
  nb_words += count_words(file);
  fclose(file);
  while (obj->options[i])
    {
      if (obj->options[i] == 'N')
	{
	  file = safe_ropen(NUME_FILE);
	  nb_words += count_words(file);
	  fclose(file);	  
	}
      if (obj->options[i] == 'S')
	{
	  file = safe_ropen(SPEC_FILE);
	  nb_words += count_words(file);
	  fclose(file);	  
	}
      ++i;
    }
  obj->nb_words = nb_words;
}

char	**get_words(char *file_name, t_obj *obj)
{
  FILE  *file;
  char  **word_array;
  char  word[SIZEMAX];
  int   word_len;
  int   i;
  int	j;

  i = 0;
  j = 0;
  word_len = 0;
  count_all_words(file_name, obj);
  word_array = safe_malloc((obj->nb_words * sizeof(char*)) + 1);
  file = safe_ropen(file_name);
  while (fgets(word, SIZEMAX, file) != NULL)
    {
      word_len = strlen(word);
      word[word_len - 1] = '\0';
      word_array[i] = safe_malloc(word_len);
      word_array[i] = strcpy(word_array[i], word);
      ++i;
    }
  fclose(file);  
  while (obj->options[j])
    {
      if (obj->options[j] == 'N')
	{
	  file = safe_ropen(NUME_FILE);
	  while (fgets(word, SIZEMAX, file) != NULL)
	    {
	      word_len = strlen(word);
	      word[word_len - 1] = '\0';
	      word_array[i] = safe_malloc(word_len);
	      word_array[i] = strcpy(word_array[i], word);
	      ++i;
	    }
	  fclose(file);
	}
      if (obj->options[j] == 'S')
	{
	  file = safe_ropen(SPEC_FILE);
	  while (fgets(word, SIZEMAX, file) != NULL)
	    {
	      word_len = strlen(word);
	      word[word_len - 1] = '\0';
	      word_array[i] = safe_malloc(word_len);
	      word_array[i] = strcpy(word_array[i], word);
	      ++i;
	    }
	  fclose(file);
	}
      ++j;
    }
  word_array[i] = '\0';

  return(word_array);
}
