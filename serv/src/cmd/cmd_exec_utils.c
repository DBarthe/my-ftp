/*
** cmd_exec_utils.c for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/serv/src/cmd
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Thu Apr 10 13:27:17 2014 Barthelemy Delemotte
** Last update Fri Apr 11 18:25:59 2014 Barthelemy Delemotte
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
  char			*sys_arg;

  if (self->arg && strcmp(self->arg, "-a") == 0)
    cmd_exec_system("ls -l --color -a", session);
  else if (self->arg)
    {
      sys_arg = malloc((strlen(self->arg) +
			strlen("ls -l --color ") + 1) * sizeof(char));
      if (sys_arg == NULL)
	return (false);
      strcpy(sys_arg, "ls -l --color ");
      strcat(sys_arg, self->arg);
      cmd_exec_system(sys_arg, session);
    }
  else
    cmd_exec_system("ls -l --color", session);
  return (true);
}

static bool		cd_error(t_session *session, const char *prefix)
{
  send_str(session->fd, "[ERROR] failed to change directory\n");
  if (prefix)
    perror("getcwd");
  return (false);
}

bool			cmd_exec_cd(t_cmd *self, t_session *session)
{
  char			*old_cwd;
  char			*new_cwd;
  bool			ret;

  old_cwd = NULL;
  new_cwd = NULL;
  ret = true;
  if ((old_cwd = get_current_dir_name()) == NULL)
    ret = cd_error(session, "getcwd");
  else if (chdir(self->arg ? self->arg : session->root) == 0)
    {
      if ((new_cwd = get_current_dir_name()) == NULL ||
	  strncmp(new_cwd, session->root, strlen(session->root)) != 0)
	{
	  (void)chdir(old_cwd);
	  ret = cd_error(session, NULL);
	}
      else
	send_str(session->fd, "[SUCCESS] directory successfully changed\n");
    }
  else
    cd_error(session, NULL);
  free(old_cwd);
  free(new_cwd);
  return (ret);
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
