/*
** main.c for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/cli/src
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Fri Apr 11 19:53:07 2014 Barthelemy Delemotte
** Last update Fri Apr 11 21:59:10 2014 Barthelemy Delemotte
*/

#include		<stdlib.h>
#include		<stdio.h>
#include		<string.h>
#include		<sys/types.h>
#include		<sys/socket.h>
#include		<netinet/in.h>
#include		<netdb.h>
#include		<unistd.h>
#include		<stdbool.h>

#include		"utils.h"
#include		"socket.h"

static int		setup(const char *hostname, int port_no)
{
  int			socket_fd;
  struct hostent	*host;
  struct sockaddr_in	serv_addr;

  if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    diep("socket");
  if ((host = gethostbyname(hostname)) == NULL)
    {
      fprintf(stderr, "ftp: %s: name or service not known\n", hostname);
      exit(EXIT_FAILURE);
    }
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  memcpy(&serv_addr.sin_addr.s_addr, host->h_addr, host->h_length);
  serv_addr.sin_port = htons(port_no);
  if (connect(socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    diep("connect");
  return (socket_fd);
}

static char		*get_input_line(void)
{
  static char		*line = NULL;
  static size_t		len = 0;

  if (getline(&line, &len, stdin) == -1)
    {
      free(line);
      return (NULL);
    }
  return (line);
}

static void		read_response(int socket_fd)
{
  char			buffer;
  ssize_t		ret;

  while ((ret = read(socket_fd, &buffer, 1)) > 0 &&
	 (unsigned char)buffer != 0xff)
    write(1, &buffer, 1);
}

static void		do_cmd(int socket_fd, char *line, bool *quit)
{
  char			**tab;
  int			i;


  send_str(socket_fd, line);
  if (strlen(line) > 0 && line[strlen(line) - 1] == '\n')
    line[strlen(line) - 1] = '\0';
  tab = my_str_to_wordtab(line);
  if (tab[0])
    {
      printf("file = [%s]\n", tab[1]);
      if (strcmp(tab[0], "quit") == 0)
	*quit = true;
      else if (tab[1] && strcmp(tab[0], "put") == 0)
	send_file(socket_fd, tab[1]);
      else if (tab[1] && strcmp(tab[0], "get") == 0)
	receiv_file(socket_fd, tab[1]);
    }
  i = 0;
  while (tab[i])
    {
      free(tab[i]);
      i++;
    }
  free(tab);
}

static void		run(int socket_fd)
{
  bool			quit;
  char			*line;

  line = NULL;
  quit = false;
  while (!quit)
    {
      line = get_input_line();
      do_cmd(socket_fd, line, &quit);
      read_response(socket_fd);
    }
  free(line);
}

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
