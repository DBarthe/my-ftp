/*
** my_str_to_wordtab.c for libmy in /home/delemo_b/epitech_1/wolf3d/lib/my
**
** Made by barthelemy delemotte
** Login   <delemo_b@epitech.net>
**
** Started on  Tue Dec 18 11:41:08 2012 barthelemy delemotte
** Last update Fri Apr 11 21:32:24 2014 Barthelemy Delemotte
*/

#include	<stdlib.h>
#include	<string.h>
#include	<stdio.h>

static void	*xmalloc(size_t size)
{
  void		*ptr;

  ptr = malloc(size);
  if (!ptr)
    {
      fprintf(stderr, "malloc has failed\n");
      exit(EXIT_FAILURE);
    }
  return (ptr);
}

static char	*get_word_from_str(const char *str)
{
  int		i;
  char		*word;

  i = 0;
  while (str[i] && str[i] != ' ' && str[i] != '\t')
    {
      i++;
    }
  word = xmalloc((i + 1) * sizeof(char));
  strncpy(word, str, i);
  word[i] = '\0';
  return (word);
}

static char	**cut_string(const char *str, char **wordtab)
{
  int		i;
  int		nb_word;

  i = 0;
  nb_word = 0;
  while (str[i])
    {
      if ((str[i] == ' ' || str[i] == '\t') && str[i + 1] && str[i + 1] != ' '
	  && str[i + 1] != '\t')
	wordtab[nb_word++] = get_word_from_str(str + i + 1);
      else if (i == 0 && str[i] != ' ' && str[i] != '\t')
        wordtab[nb_word++] = get_word_from_str(str);
      i++;
    }
  wordtab[nb_word] = NULL;
  return (wordtab);

}

char		**my_str_to_wordtab(const char *str)
{
  char		**wordtab;
  int		i;
  int		nb_word;

  i = 0;
  nb_word = 0;
  while (str[i])
    {
      if (str[i] != ' ' && str[i] != '\t' && (i == 0 || str[i - 1] == ' '
					      || str[i - 1] == '\t'))
	nb_word++;
      i++;
    }
  wordtab = xmalloc((nb_word + 1) * sizeof(char *));
  return (cut_string(str, wordtab));
}
