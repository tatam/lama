/*
** lama_file.c
** 
** Made by Tatam
** Login   <tatam@protonmail.com>
** 
** Started on  Wed Sep 28 08:38:46 2016 Tatam
** Last update Tue Jan 16 22:10:44 2018 Tatam
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

void	add_word(t_lst *list, char **words, t_obj *obj)
{
  t_wd	*curr_word;
  t_wd	*new_word;
  int	word_len;
  int	i;

  i = 0;
  while (words[i])
    {
      word_len = strlen(words[i]);
      new_word = safe_malloc(sizeof(*new_word) + 1);
      new_word->simple = safe_malloc(word_len);
      new_word->first_maj = safe_malloc(word_len);
      new_word->leet = safe_malloc(word_len);
      new_word->simple = strcpy(new_word->simple, words[i]);
      new_word->first_maj_status = alter_first_maj(new_word->first_maj, words[i]);
      new_word->leet_status = alter_leet(new_word->leet, words[i], obj);
      new_word->next = NULL;
      new_word->alias = NULL;
      curr_word = list->first;
      while (curr_word->next != NULL)
	curr_word = curr_word->next;
      if (i == 0)
	{
	  curr_word->next = new_word;
	  while (curr_word->alias != NULL)
	    {
	      curr_word = curr_word->alias;
	      curr_word->next = new_word;
	    }
	}
      else
	{	  
	  while (curr_word->alias != NULL)
	    curr_word = curr_word->alias;
	  curr_word->alias = new_word;
	}
      ++i;
    } 
}

t_lst	*init_list(char **words, t_obj *obj)
{
  t_lst *list;
  t_wd	*word;
  t_wd	*curr_word;
  int	word_len;
  int	i;

  i = 0;
  list = safe_malloc(sizeof(*list) + 1);
  while (words[i])
    {
      word_len = strlen(words[i]);
      word = safe_malloc(sizeof(*word) + 1);    
      word->simple = safe_malloc(word_len);
      word->first_maj = safe_malloc(word_len);
      word->leet = safe_malloc(word_len);
      word->simple = strcpy(word->simple, words[i]);
      word->first_maj_status = alter_first_maj(word->first_maj, words[i]);
      word->leet_status = alter_leet(word->leet, words[i], obj);
      word->next = NULL;
      word->alias = NULL;
      if (i == 0)
	list->first = word;
      else
	{
	  curr_word = list->first;
	  while (curr_word->alias != NULL)
	    curr_word = curr_word->alias;
	  curr_word->alias = word;
	}
      ++i;
    }
  
  return(list);
}

// RM THIS
void	debug(t_lst *list)
{
  t_wd	*w;
  int	bool;

  bool = 0;
  w = list->first;
  while (w->next != NULL || w->alias != NULL)
    {
      if (w->alias == NULL)
	fprintf(stderr, "%s", w->simple);
      else
	{
	  bool = 1;
	  while (w->alias != NULL)
	    {
	      fprintf(stderr, "%s ", w->simple);
	      w = w->alias;
	    }
	  fprintf(stderr, "%s ", w->simple);	  
	}
      fprintf(stderr, "\n");
      if (w->next != NULL)
	{
	  bool = 0;
	  w = w->next;
	}
    }
  if (bool == 0)
    fprintf(stderr, "%s\n", w->simple);

  if (w->next == NULL)
    fprintf(stderr, "[x] (%s)->next == NULL\n", w->simple);
  if (w->alias == NULL)
    fprintf(stderr, "[x] (%s)->alias == NULL\n", w->simple);
  fprintf(stderr, "-----------------------------------\n");
}

t_lst	*get_words_list(char *file_name, t_obj *obj)
{
  t_lst	*list;
  FILE	*file;
  char	**words;
  char	word[SIZEMAX];
  int	i;

  i = 0;
  count_all_words(file_name, obj);
  file = safe_ropen(file_name);
  list = NULL;
  while (fgets(word, SIZEMAX, file) != NULL)
    {      
      words = split_pipe(word);
      if (words != NULL)
	{
	  if (list == NULL)
	    list = init_list(words, obj);
	  else
	    add_word(list, words, obj);
	}
      free(words);
    }
  fclose(file);
  while (obj->options[i])
    {
      if (obj->options[i] == 'N')
	{
	  file = safe_ropen(NUME_FILE);
	  while (fgets(word, SIZEMAX, file) != NULL)
	    {
	      words = split_pipe(word);
	      if (words != NULL)
		add_word(list, words, obj);
	      free(words);
	    }
	  fclose(file);
	}
      if (obj->options[i] == 'S')
	{
	  file = safe_ropen(SPEC_FILE);
	  while (fgets(word, SIZEMAX, file) != NULL)
	    {
	      words = split_pipe(word);
	      if (words != NULL)
		add_word(list, words, obj);
	      free(words);
	    }
	  fclose(file);
	}
      ++i;
    }
  //  debug(list); // DEBUG, RM THIS

  return(list);
}
