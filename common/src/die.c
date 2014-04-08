/*
** die.c for mmmmyftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/serv
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Tue Apr  8 14:57:53 2014 Barthelemy Delemotte
** Last update Tue Apr  8 15:11:07 2014 Barthelemy Delemotte
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<stdarg.h>

void		die(const char *message)
{
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}

void		diep(const char *prefix)
{
  perror(prefix);
  exit(EXIT_FAILURE);
}

void		dief(const char *fmt, ...)
{
  va_list	ap;

  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);
  exit(EXIT_FAILURE);
}
