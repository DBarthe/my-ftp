/*
** cmd_exec_system.c for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/serv/src/cmd
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Wed Apr  9 17:17:26 2014 Barthelemy Delemotte
** Last update Wed Apr  9 17:48:57 2014 Barthelemy Delemotte
*/

#include		<unistd.h>
#include		<stdlib.h>
#include		<stdio.h>
#include		<sys/wait.h>

#include		"cmd.h"
#include		"socket.h"

static void		close_pipe(int pipe_fd[2])
{
  close(pipe_fd[0]);
  close(pipe_fd[1]);
}

static void		cmd_exec_child(const char *cmd, int pipe_fd[2],
				       t_session *session)
{
  close(pipe_fd[0]);
  if (dup2(pipe_fd[1], 1) == -1 ||
      dup2(pipe_fd[1], 2) == -1)
    {
      perror("dup2");
      exit(EXIT_FAILURE);
    }
  if (system(cmd) == -1)
    {
      send_str(session->fd, "[ERROR] internal error\n");
      exit(EXIT_FAILURE);
    }
  exit(EXIT_SUCCESS);
}

static void		cmd_send_output(t_session *session, int in)
{
  char			buffer[256];
  int			ret;

  while ((ret = read(in, buffer, 256)) > 0)
    send_raw(session->fd, buffer, ret);
}

bool			cmd_exec_system(const char *cmd, t_session *session)
{
  int			pipe_fd[2];
  pid_t			pid;

  if (pipe(pipe_fd) == -1)
    {
      perror("pipe");
      send_str(session->fd, "[ERROR] internal error\n");
      return (false);
    }
  if ((pid = fork()) == -1)
    {
      perror("fork");
      send_str(session->fd, "[ERROR] internal error\n");
      close_pipe(pipe_fd);
      return (false);
    }
  else if (!pid)
    cmd_exec_child(cmd, pipe_fd, session);
  close(pipe_fd[1]);
  cmd_send_output(session, pipe_fd[0]);
  wait(NULL);
  close(pipe_fd[0]);
  return (true);
}
