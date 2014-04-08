/*
** server.c for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/serv
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Tue Apr  8 14:36:21 2014 Barthelemy Delemotte
** Last update Tue Apr  8 15:48:44 2014 Barthelemy Delemotte
*/

#include		<unistd.h>
#include		<stdlib.h>
#include		<stdio.h>
#include		<string.h>
#include		<sys/types.h>
#include		<sys/socket.h>
#include		<netinet/in.h>

#include		"server.h"
#include		"utils.h"
#include		"defines.h"

static int		make_socket(uint16_t port)
{
  int			socket_fd;
  struct sockaddr_in	serv_addr;
  int			yes;

  yes = 1;
  DEBUG_PRINT("creating socket");
  if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    diep("socket");
  if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    die("setsockopt");
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(port);
  DEBUG_PRINT("binding socket");
  if (bind(socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    diep("bind");
  return (socket_fd);
}

void			server_setup(t_server *self, uint16_t port,
				     t_accept_callback callback)
{
  DEBUG_PRINT("server setup");
  memset(self, 0, sizeof(*self));
  self->socket_fd = make_socket(port);
  self->callback = callback;
  DEBUG_PRINT("start listening");
  if (listen(self->socket_fd, SERVER_BACKLOG) == -1)
    die("listen");
}

static void		server_loop_body(t_server *self)
{
  int			cli_fd;
  struct sockaddr_in	cli_addr;
  socklen_t		cli_len;
  pid_t			pid;

  cli_len = sizeof(cli_addr);
  DEBUG_PRINT("waiting for accepting new client");
  cli_fd = accept(self->socket_fd, (struct sockaddr *)&cli_addr, &cli_len);
  if (cli_fd < 0)
    diep("accept");
  DEBUG_PRINT("new client accepted");
  pid = fork();
  if (pid == -1)
    diep("fork");
  else if (pid == 0)
    {
      close(self->socket_fd);
      if (self->callback)
	self->callback(cli_fd);
      close(cli_fd);
      exit(EXIT_SUCCESS);
    }
  close(cli_fd);
}

void			server_run(t_server *self)
{
  DEBUG_PRINT("starting server loop");
  while (42)
    {
      server_loop_body(self);
    }
}
