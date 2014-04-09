/*
** session_run.c for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/serv/src
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Tue Apr  8 18:16:25 2014 Barthelemy Delemotte
** Last update Wed Apr  9 16:31:26 2014 Barthelemy Delemotte
*/

#include		<stdlib.h>
#include		<stdio.h>

#include		"session.h"
#include		"cmd.h"
#include		"defines.h"

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
  t_cmd			cmd;
  char			*cmd_raw;

  while (!self->quit)
    {
      cmd_raw = session_fetch_cmd(self);
      DEBUG_PRINT("new command");
      printf("cmd=[%s]\n", cmd_raw);
      if (cmd_parse(&cmd, cmd_raw, self))
	(void)cmd_exec(&cmd, self);
      else
	{
	  DEBUG_PRINT("command parsing failed");
	}
      cmd_dump(&cmd);
      cmd_clean(&cmd);
    }
}
