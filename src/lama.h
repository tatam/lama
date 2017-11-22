/*
** lama.h
** 
** Made by Tatam
** Login   <tatam@protonmail.com>
** 
** Started on  Wed Sep 28 08:47:14 2016 Tatam
** Last update Sat Nov 11 17:34:54 2017 Tatam
*/
// Includes
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

// Defines
#define SIZEMAX 1024
#define LEET_FILE "/etc/lama/leet.lst"
#define SPEC_FILE "/etc/lama/special.lst"
#define NUME_FILE "/etc/lama/numeric.lst"

// Function pointer & Struct
typedef struct t_obj t_obj;
typedef	void (*t_opt)(int interval, t_obj *obj);
struct  t_obj
{
  t_opt	*pt_function;
  char	**leet;
  char	**words;
  char	*options;
  int	*pt_words;
  int	nb_words;
  int	interval;
  int	cur_perm;
  int	min;
  int	max;
  int	res;
};
typedef struct t_num t_num;
struct	t_num
{
  long	nb_simple;
  long	nb_first_maj;
  long	nb_all_maj;
  long	nb_leet;
  long	nb_total;
  char	*simple;
  char	*first_maj;
  char	*all_maj;
  char	*leet;
  char	*total;
};
typedef	struct t_len t_len;
struct	t_len
{
  int	len_words;
  float	avg_len;
  long	len_simple;
  long	len_first_maj;
  long	len_all_maj;
  long	len_leet;
  long	len_total;
  char	*simple;
  char	*first_maj;
  char	*leet;
  char	*all_maj;
  char	*total;
};

// Prototypes
char	**get_words(char *file, t_obj *obj);
char	*human_nb_convert(long nb);
char	*human_len_convert(long nb);
t_obj   *check_arg(int argc, char **argv);
t_num	*count_init(t_obj *obj);
t_len	*len_init(t_obj *obj);
FILE    *safe_ropen(char *file_name);
void	*safe_malloc(int value);
void    mix(int interval, t_obj *obj);
void    print_simple(int interval, t_obj *obj);
void    print_first_maj(int interval, t_obj *obj);
void    print_all_maj(int interval, t_obj *obj);
void    print_leet(int interval, t_obj *obj);
long	count_simple(t_obj *obj);
long	count_first_maj(t_obj *obj, t_num *num);
long	count_all_maj(t_obj *obj, t_num *num);
long	count_leet(t_obj *obj, t_num *num);
long	len_simple(t_obj *obj, t_len *len);
long	len_first_maj(t_obj *obj, t_len *len);
long	len_leet(t_obj *obj, t_len *len);
long	len_all_maj(t_obj *obj, t_len *len);
int	calcul_word(char *soft, t_obj *obj);
int	len_words(t_obj *obj);
int	count_words(FILE *file);
