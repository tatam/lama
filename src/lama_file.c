/*
** lama_file.c
** 
** Made by Tatam
** Login   <tatam@protonmail.com>
** 
** Started on  Wed Sep 28 08:38:46 2016 Tatam
** Last update Sun Dec 17 10:37:48 2017 Tatam
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

void	add_word(t_lst *list, char *word, t_obj *obj)
{
  t_wd	*curr_word;
  t_wd	*new_word;
  int	word_len;

  word_len = strlen(word);
  word[word_len - 1] = '\0';
  new_word = safe_malloc(sizeof(*new_word) + 1);
  new_word->simple = safe_malloc(word_len);
  new_word->first_maj = safe_malloc(word_len);
  new_word->leet = safe_malloc(word_len);
  new_word->simple = strcpy(new_word->simple, word);
  new_word->first_maj_status = alter_first_maj(new_word->first_maj, word);
  new_word->leet_status = alter_leet(new_word->leet, word, obj);
  curr_word = list->first;
  while (curr_word->next != NULL)
    curr_word = curr_word->next;
  curr_word->next = new_word;
  new_word->next = NULL;
}

t_lst	*init_list(char *word, t_obj *obj)
{
  t_lst *list;
  t_wd	*first_word;
  int	word_len;

  word_len = strlen(word);
  word[word_len - 1] = '\0';
  list = safe_malloc(sizeof(*list) + 1);
  first_word = safe_malloc(sizeof(*first_word) + 1);
  first_word->simple = safe_malloc(word_len);
  first_word->first_maj = safe_malloc(word_len);
  first_word->leet = safe_malloc(word_len);
  first_word->simple = strcpy(first_word->simple, word);
  first_word->first_maj_status = alter_first_maj(first_word->first_maj, word);
  first_word->leet_status = alter_leet(first_word->leet, word, obj);
  first_word->next = NULL;
  list->first = first_word;

  return(list);
}

t_lst *get_words_list(char *file_name, t_obj *obj)
{
  t_lst	*list;
  FILE	*file;
  char	word[SIZEMAX];
  int	i;

  i = 0;
  count_all_words(file_name, obj);
  file = safe_ropen(file_name);
  list = NULL;
  while (fgets(word, SIZEMAX, file) != NULL)
    {
      if (list == NULL)
	list = init_list(word, obj);
      else
	add_word(list, word, obj);
    }
  fclose(file);
  while (obj->options[i])
    {
      if (obj->options[i] == 'N')
	{
	  file = safe_ropen(NUME_FILE);
	  while (fgets(word, SIZEMAX, file) != NULL)
	    add_word(list, word, obj);
	  fclose(file);
	}
      if (obj->options[i] == 'S')
	{
	  file = safe_ropen(SPEC_FILE);
	  while (fgets(word, SIZEMAX, file) != NULL)
	    add_word(list, word, obj);
	  fclose(file);
	}
      ++i;
    }
  
  return(list);
}
