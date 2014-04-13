/*
** session_run.c for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/serv/src
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Tue Apr  8 18:16:25 2014 Barthelemy Delemotte
** Last update Sun Apr 13 15:14:02 2014 Barthelemy Delemotte
*/

#include		<stdlib.h>
#include		<stdio.h>

#include		"session.h"
#include		"cmd.h"
#include		"defines.h"
#include		"socket.h"

static char		*session_fetch_cmd(t_session *self)
{
  while (!swing_is_cmd_available(&self->swing))
    {
      if (swing_feed(&self->swing, self->fd) == false)
	{
	  self->quit = true;
	  return (NULL);
	}
    }
  return (swing_pull_cmd(&self->swing));
}

void			session_run(t_session *self)
{
  t_cmd			cmd;
  char			*cmd_raw;

  while (!self->quit)
    {
      if ((cmd_raw = session_fetch_cmd(self)))
	{
	  DEBUG_PRINT("new command");
	  if (cmd_parse(&cmd, cmd_raw, self))
	    (void)cmd_exec(&cmd, self);
	  else
	    {
	      DEBUG_PRINT("command parsing failed");
	    }
	  send_eot(self->fd);
	  cmd_clean(&cmd);
	}
      else
	printf("connexion interupted\n");
    }
}
