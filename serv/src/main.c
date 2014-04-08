/*
** main.c for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Tue Apr  8 12:07:45 2014 Barthelemy Delemotte
** Last update Tue Apr  8 17:26:33 2014 Barthelemy Delemotte
*/

#include		<stdlib.h>
#include		<stdio.h>

#include		"server.h"
#include		"swing.h"

static void		tmp_callback(int fd)
{
  t_swing		swing;
  char			*cmd;
  char			*rest;
  size_t		size;

  swing_ctor(&swing);
  while (!swing_is_cmd_available(&swing))
    {
      swing_feed(&swing, fd);
      swing_dump(&swing);
    }

  cmd = swing_pull_cmd(&swing);
  rest = swing_pull_rest(&swing, &size);
  printf("cmd=[%s] rest=[%s]\n", cmd, rest);
  free(cmd);
  free(rest);
  swing_dtor(&swing);
}

int			main(/*int ac, char **av*/void)
{
  t_server		server;

  server_setup(&server, 4242, &tmp_callback);
  server_run(&server);
  return (EXIT_SUCCESS);
}
