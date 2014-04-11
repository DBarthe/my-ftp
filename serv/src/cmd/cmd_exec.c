/*
** cmd_exec.c for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/serv/src/cmd
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Wed Apr  9 17:00:14 2014 Barthelemy Delemotte
** Last update Fri Apr 11 21:48:15 2014 Barthelemy Delemotte
*/

#include		<string.h>
#include		<errno.h>
#include		<stdio.h>

#include		"cmd.h"
#include		"socket.h"

static bool		cmd_exec_get(t_cmd *self, t_session *session)
{
  if (!self->arg)
    {
      send_str(session->fd, "[ERROR] command 'get' must take an argument\n");
      return (false);
    }
  if (send_file(session->fd, self->arg) == false)
    {
      perror("get");
      send_fmt(session->fd, "[ERROR] get: %s\n", strerror(errno));
      return (false);
    }
  else
    send_str(session->fd, "[SUCCESS]\n");
  return (true);
}

static bool		cmd_exec_put(t_cmd *self, t_session *session)
{
  if (!self->arg)
    {
      send_str(session->fd, "[ERROR] command 'put' must take an argument\n");
      return (false);
    }
  if (receiv_file(session->fd, self->arg) == false)
    {
      perror("put");
      send_fmt(session->fd, "[ERROR] put: %s\n", strerror(errno));
      return (false);
    }
  else
    send_str(session->fd, "[SUCCESS]\n");
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
  send_eot(session->fd);
  return (ret);
}

bool			cmd_exec(t_cmd *self, t_session *session)
{
  return (cmd_switch(self, session));
}
