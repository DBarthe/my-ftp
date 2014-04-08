/*
** main.c for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Tue Apr  8 12:07:45 2014 Barthelemy Delemotte
** Last update Tue Apr  8 15:39:02 2014 Barthelemy Delemotte
*/

#include		<stdlib.h>

#include		"server.h"

int			main(/*int ac, char **av*/void)
{
  t_server		server;

  server_setup(&server, 4242, NULL);
  server_run(&server);
  return (EXIT_SUCCESS);
}
