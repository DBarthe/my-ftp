/*
** run.c for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Sun Apr 13 13:47:46 2014 Barthelemy Delemotte
** Last update Sun Apr 13 14:18:04 2014 Barthelemy Delemotte
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

int			setup(const char *hostname, int port_no)
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

  printf("ftp> ");
  fflush(stdin);
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

void			run(int socket_fd)
{
  bool			quit;
  char			*line;

  printf("                    .-._   _ _ _ _ _ _ _ _\n"
	 "         .-''-.__.-'00  '-' ' ' ' ' ' ' ' '-.\n"
	 "         '.___ '    .   .--_'-' '-' '-' _'-' '.\n"
	 "          V: V 'vv-'   '_   '.       .'  _..' '.'.\n"
	 "            '=.____.=_.--'   :_.__.__:_   '.   : :\n"
	 "                    (((____.-'        '-.  /   : :\n"
	 "                                      (((-'\\ .' /\n"
	 "                                    _____..'  .'\n"
	 "                                   '-._____.-'\n");
  line = NULL;
  quit = false;
  while (!quit && (line = get_input_line()))
    {
      do_cmd(socket_fd, line, &quit);
      read_response(socket_fd);
    }
  free(line);
}
