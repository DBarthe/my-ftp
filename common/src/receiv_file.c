/*
** receiv_file.c for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/common/src
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Fri Apr 11 19:41:13 2014 Barthelemy Delemotte
** Last update Fri Apr 11 22:47:24 2014 Barthelemy Delemotte
*/

#include		<unistd.h>
#include		<fcntl.h>
#include		<stdlib.h>

#include		"socket.h"
#include		"utils.h"
#include		"defines.h"

static void		receiv_data(int remote_fd, int file_fd,
				    long long int file_size)
{
  char			buffer[1024];
  ssize_t		ret;

  while (file_size > 0 &&
	 (ret = read(remote_fd, buffer, file_size < 1024 ?
		     file_size : 1024)) > 0)
    {
      write(file_fd, buffer, ret);
      file_size -= ret;
    }
}

bool			receiv_file(int remote_fd, const char *file)
{
  long long int		file_size;
  int			file_fd;

  if (read(remote_fd, (char *)&file_size, sizeof(long long int)) !=
      sizeof(long long int) || file_size < 0)
    return (false);
  if (file_size < 0)
    return (false);
  if ((file_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0664)) == -1)
    return (false);
  receiv_data(remote_fd, file_fd, file_size);
  close(file_fd);
  return (true);
}
