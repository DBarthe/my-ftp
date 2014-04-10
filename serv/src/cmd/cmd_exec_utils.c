/*
** cmd_exec_utils.c for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/serv/src/cmd
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Thu Apr 10 13:27:17 2014 Barthelemy Delemotte
** Last update Thu Apr 10 13:32:43 2014 Barthelemy Delemotte
*/

#define			_GNU_SOURCE
#include		<unistd.h>
#include		<string.h>
#include		<stdlib.h>
#include		<stdio.h>

#include		"cmd.h"
#include		"socket.h"

bool			cmd_exec_ls(t_cmd *self, t_session *session)
{
  (void)self;
  if (self->arg && strcmp(self->arg, "-a") == 0)
    cmd_exec_system("ls -l --color -a", session);
  else
    cmd_exec_system("ls -l --color", session);
  return (true);
}

bool			cmd_exec_cd(t_cmd *self, t_session *session)
{
  if (chdir(self->arg ? self->arg : session->root) == 0)
    send_str(session->fd, "[SUCCESS] directory successfully changed\n");
  else
    {
      send_str(session->fd, "[ERROR] failed to change directory\n");
      return (false);
    }
  return (true);
}

bool			cmd_exec_pwd(t_cmd *self, t_session *session)
{
  char			*cwd;

  (void)self;
  if ((cwd = get_current_dir_name()) == NULL)
    {
      send_str(session->fd, "[ERROR] could not print working directory\n");
      perror("getcwd");
      return (false);
    }
  send_str(session->fd, "[SUCCESS] \"");
  send_str(session->fd, cwd);
  send_str(session->fd, "\"\n");
  free(cwd);
  return (true);
}

bool			cmd_exec_quit(t_cmd *self, t_session *session)
{
  (void)self;
  session->quit = true;
  send_str(session->fd, "[SUCCESS] goodbye\n");
  return (true);
}
