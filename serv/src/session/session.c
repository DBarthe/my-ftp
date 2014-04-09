/*
** session.c for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/serv/src
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Tue Apr  8 18:05:33 2014 Barthelemy Delemotte
** Last update Wed Apr  9 18:03:26 2014 Barthelemy Delemotte
*/

#define			_GNU_SOURCE
#include		<unistd.h>
#include		<stdio.h>
#include		<stdlib.h>

#include		"session.h"
#include		"swing.h"
#include		"utils.h"

void			session_ctor(t_session *self, int cli_fd)
{
  self->fd = cli_fd;
  swing_ctor(&self->swing);
  self->quit = false;
  if ((self->root = get_current_dir_name()) == NULL)
    {
      diep("getcwd");
    }
}

void			session_dtor(t_session *self)
{
  close(self->fd);
  swing_dtor(&self->swing);
  free(self->root);
}
