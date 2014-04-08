/*
** main.c for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Tue Apr  8 12:07:45 2014 Barthelemy Delemotte
** Last update Tue Apr  8 18:09:58 2014 Barthelemy Delemotte
*/

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

int			main(/*int ac, char **av*/void)
{
  t_server		server;

  server_setup(&server, 4242, &accept_callback);
  server_run(&server);
  return (EXIT_SUCCESS);
}
