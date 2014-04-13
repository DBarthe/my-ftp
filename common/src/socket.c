/*
** socket.c for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/common
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Tue Apr  8 18:52:57 2014 Barthelemy Delemotte
** Last update Sun Apr 13 14:23:23 2014 Barthelemy Delemotte
*/

#include		<stdio.h>
#include		<unistd.h>
#include		<stdarg.h>
#include		<string.h>

#include		"utils.h"
#include		"socket.h"

bool			send_raw(int socket_fd, const char *buffer,
				 size_t size)
{
  ssize_t		ret;

  ret = 0;
  while (size > 0 && (ret = write(socket_fd, buffer, size)) > 0)
    {
      buffer += ret;
      size -= (size_t)ret;
    }
  return (ret == -1 ? false : true);
}


bool			send_str(int socket_fd, const char *str)
{
  return (send_raw(socket_fd, str, strlen(str)) == -1 ? false : true);
}


bool			send_fmt(int socket_fd, const char *fmt, ...)
{
  static char		buffer[1024 + 1];
  va_list		ap;
  int			ret;

  va_start(ap, fmt);
  ret = vsnprintf(buffer, sizeof(buffer), fmt, ap);
  va_end(ap);
  return (ret < 0 ? false :  send_raw(socket_fd, buffer,
				      ret > 1024 ? 1024 : ret));
}

bool			send_eot(int socket_fd)
{
  unsigned char		eot;

  eot = 0xff;
  return (send_raw(socket_fd, (char *)&eot, 1));
}
