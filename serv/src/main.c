/*
** main.c for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Tue Apr  8 12:07:45 2014 Barthelemy Delemotte
** Last update Sun Apr 13 13:55:17 2014 Barthelemy Delemotte
*/

#include		<unistd.h>
#include		<stdlib.h>
#include		<stdio.h>

#include		"server.h"
#include		"session.h"

static void		accept_callback(int fd)
{
  t_session		session;

  session_ctor(&session, fd);
  session_run(&session);
  session_dtor(&session);
}

int			main(int ac, char **av)
{
  t_server		server;

  if (ac < 2)
    {
      fprintf(stderr, "usage: %s port_no\n", av[0]);
      exit(EXIT_FAILURE);
    }
  server_setup(&server, atoi(av[1]), &accept_callback);
  server_run(&server);
  return (EXIT_SUCCESS);
}
