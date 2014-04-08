/*
** socket.c for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/common
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Tue Apr  8 18:52:57 2014 Barthelemy Delemotte
** Last update Tue Apr  8 19:02:16 2014 Barthelemy Delemotte
*/

#include		<stdio.h>
#include		<unistd.h>
#include		<stdarg.h>
#include		<string.h>

#include		"utils.h"
#include		"socket.h"

bool			send_str(int socket_fd, const char *str)
{
  return (write(socket_fd, str, strlen(str)) == -1 ? false : true);
}

bool			send_raw(int socket_fd, const char *buffer,
				 size_t size)
{
  return (write(socket_fd, buffer, size) == -1 ? false : true);
}

bool			send_fmt(int socket_fd, const char *fmt, ...)
{
  static char		buffer[1024];
  va_list		ap;

  va_start(ap, fmt);
  vsnprintf(buffer, sizeof(buffer), fmt, ap);
  va_end(ap);
  return (send_str(socket_fd, buffer));
}
