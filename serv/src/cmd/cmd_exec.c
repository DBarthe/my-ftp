/*
** cmd_exec.c for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/serv/src/cmd
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Wed Apr  9 17:00:14 2014 Barthelemy Delemotte
** Last update Wed Apr  9 17:45:51 2014 Barthelemy Delemotte
*/

#include		<string.h>

#include		"cmd.h"
#include		"socket.h"

static bool		cmd_exec_ls(t_cmd *self, t_session *session)
{
  (void)self;
  cmd_exec_system("ls -l", session);
  return (true);
}
static bool		cmd_exec_cd(t_cmd *self, t_session *session)
{
  (void)self; (void)session;
  return (true);
}
static bool		cmd_exec_get(t_cmd *self, t_session *session)
{
  (void)self; (void)session;
  return (true);
}
static bool		cmd_exec_put(t_cmd *self, t_session *session)
{
  (void)self; (void)session;
  return (true);
}
static bool		cmd_exec_pwd(t_cmd *self, t_session *session)
{
  (void)self; (void)session;
  return (true);
}
static bool		cmd_exec_quit(t_cmd *self, t_session *session)
{
  (void)self; (void)session;
  return (true);
}

static bool		cmd_switch(t_cmd *self, t_session *session)
{
  bool			ret;

  if (strcmp(self->name, "ls") == 0)
    ret = cmd_exec_ls(self, session);
  else if (strcmp(self->name, "cd") == 0)
    ret = cmd_exec_cd(self, session);
  else if (strcmp(self->name, "get") == 0)
    ret = cmd_exec_get(self, session);
  else if (strcmp(self->name, "put") == 0)
    ret = cmd_exec_put(self, session);
  else if (strcmp(self->name, "pwd") == 0)
    ret = cmd_exec_pwd(self, session);
  else if (strcmp(self->name, "quit") == 0)
    ret = cmd_exec_quit(self, session);
  else
    {
      ret = false;
      send_fmt(session->fd, "[ERROR] invalid command '%s'\n", self->name);
    }
  return (ret);
}

bool			cmd_exec(t_cmd *self, t_session *session)
{
  return (cmd_switch(self, session));
}
