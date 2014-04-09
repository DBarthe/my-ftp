/*
** cmd.c for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/serv/src/cmd
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Wed Apr  9 15:20:11 2014 Barthelemy Delemotte
** Last update Wed Apr  9 17:00:30 2014 Barthelemy Delemotte
*/

#include		<stdlib.h>
#include		<stdio.h>

#include		"cmd.h"

void			cmd_clean(t_cmd *self)
{
  free(self->raw);
  self->raw = NULL;
  self->name = NULL;
  self->arg = NULL;
}

void			cmd_dump(const t_cmd *self)
{
  printf("cmd: name=\"%s\" arg=\"%s\"\n",
	 self->name ? self->name : "(nil)",
	 self->arg ? self->arg : "(nil)");
}
