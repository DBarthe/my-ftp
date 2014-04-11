/*
** send_file.c for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/common/src
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Fri Apr 11 18:33:40 2014 Barthelemy Delemotte
** Last update Fri Apr 11 22:35:31 2014 Barthelemy Delemotte
*/

#include		<stdlib.h>
#include		<unistd.h>
#include		<stdio.h>
#include		<stdbool.h>
#include		<fcntl.h>

#include		"utils.h"
#include		"socket.h"

static long long int	get_file_size(int fd)
{
  off_t			start;
  off_t			end;

  start = lseek(fd, 0, SEEK_CUR);
  end = lseek(fd, 0, SEEK_END);
  lseek(fd, 0, SEEK_SET);
  return ((long long int)(end - start));
}

static void		send_data(int remote_fd, const char *buffer,
				  long long int file_size)
{
  ssize_t		ret;

  while (file_size > 0 && (ret = write(remote_fd, buffer, file_size)) > 0)
    {
      file_size -= ret;
      buffer += ret;
    }
}

bool			send_file(int remote_fd, const char *file)
{
  long long int		file_size;
  int			file_fd;
  char			*buffer;

  file_size = -1;
  if ((file_fd = open(file, O_RDONLY)) == -1)
    {
      send_raw(remote_fd, (char *)&file_size, sizeof(long long int));
      return (false);
    }
  file_size = get_file_size(file_fd);
  if ((buffer = malloc(file_size  * sizeof(char))) == NULL)
    die("malloc has failed");
  send_raw(remote_fd, (char *)&file_size, sizeof(long long int));
  if (read(file_fd, buffer, file_size) < 0)
    return (false);
  send_data(remote_fd, buffer, file_size);
  free(buffer);
  close(file_fd);
  return (true);
}
