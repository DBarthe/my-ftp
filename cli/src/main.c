/*
** main.c for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/cli/src
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Fri Apr 11 19:53:07 2014 Barthelemy Delemotte
** Last update Sun Apr 13 13:51:07 2014 Barthelemy Delemotte
*/

#include		<stdlib.h>
#include		<stdio.h>

#include		"client.h"

int			main(int ac, char **av)
{
  int			socket_fd;

  if (ac < 3)
    {
      fprintf(stderr, "usage: %s hostname port\n", av[0]);
      return (EXIT_FAILURE);
    }
  socket_fd = setup(av[1], atoi(av[2]));
  run(socket_fd);
  return (0);
}
