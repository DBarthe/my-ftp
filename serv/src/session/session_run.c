/*
** session_run.c for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/serv/src
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Tue Apr  8 18:16:25 2014 Barthelemy Delemotte
** Last update Tue Apr  8 18:41:27 2014 Barthelemy Delemotte
*/

#include		<stdlib.h>
#include		<stdio.h>

#include		"session.h"

static char		*session_fetch_cmd(t_session *self)
{
  while (!swing_is_cmd_available(&self->swing))
    {
      swing_feed(&self->swing, self->fd);
    }
  return (swing_pull_cmd(&self->swing));
}

void			session_run(t_session *self)
{
  char			*cmd;

  while (!self->quit)
    {
      cmd = session_fetch_cmd(self);
      /*cmd_exec(cmd, self);*/
      printf("cmd=[%s]\n", cmd);
      free(cmd);
    }
}
