/*
** send_file.c for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/common/src
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Fri Apr 11 18:33:40 2014 Barthelemy Delemotte
** Last update Sun Apr 13 15:34:54 2014 Barthelemy Delemotte
*/

#include		<stdlib.h>
#include		<unistd.h>
#include		<stdio.h>
#include		<stdbool.h>
#include		<fcntl.h>
#include		<sys/stat.h>
#include		<string.h>

#include		"utils.h"
#include		"socket.h"

static long long int	get_file_size(int fd)
{
  off_t			start;
  off_t			end;

  start = lseek(fd, 0, SEEK_CUR);
  end = lseek(fd, 0, SEEK_END);
  lseek(fd, start, SEEK_SET);
  return ((long long int)(end - start));
}

static void		file_padding(int fd, char val, size_t size)
{
  char			buffer[1024];

  memset(buffer, val, size < 1024 ? size : 1024);
  while (size > 0)
    {
      send_raw(fd, buffer, size < 1024 ? size : 1024);
      size -= size < 1024 ? size : 1024;
    }
}

bool			send_file(int remote_fd, const char *file)
{
  long long int		file_size;
  int			file_fd;
  char			buffer[1024];
  ssize_t		ret;
  struct stat		sb;

  file_size = 0;
  if ((file_fd = open(file, O_RDONLY)) == -1
      || fstat(file_fd, &sb) == -1
      || (sb.st_mode & S_IFMT) != S_IFREG)
    file_size = -1;
  if (file_size == 0)
    file_size = get_file_size(file_fd);
  send_raw(remote_fd, (char *)&file_size, sizeof(long long int));
  if (file_size == -1)
    return (false);
  while ((ret = read(file_fd, buffer, 1024)) > 0)
    {
      if (send_raw(remote_fd, buffer, ret) == false)
	return (false);
      file_size -= ret;
    }
  file_padding(remote_fd, 0, (size_t)file_size);
  close(file_fd);
  return (true);
}
