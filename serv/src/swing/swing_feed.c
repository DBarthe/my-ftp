/*
** swing_feed.c for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/serv/src
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Tue Apr  8 17:41:47 2014 Barthelemy Delemotte
** Last update Sun Apr 13 13:36:24 2014 Barthelemy Delemotte
*/

#include		<unistd.h>
#include		<stdlib.h>
#include		<string.h>
#include		<assert.h>

#include		"swing.h"
#include		"utils.h"
#include		"defines.h"

static void		swing_resize(t_swing *self, size_t size)
{
  DEBUG_PRINT("resizing swing buffer");
  assert(size > self->size);
  self->buffer = realloc(self->buffer, size);
  if (self->buffer == NULL)
    die("malloc has failed");
  self->size = size;
}

bool			swing_feed(t_swing *self, int fd)
{
  static char		buffer[SWING_FEED_SIZE];
  static int		no_activity_count = 0;
  ssize_t		ret;
  size_t		i;

  DEBUG_PRINT("swing feeding");
  if ((ret = read(fd, buffer, SWING_FEED_SIZE)) < 0)
    diep("read");
  else if (ret > 0)
    no_activity_count = 0;
  else if (++no_activity_count > 10)
    return (false);
  if (self->counter + (size_t)ret > self->size)
    swing_resize(self, self->counter + (size_t)ret);
  i = 0;
  while (i < (size_t)ret)
    {
      self->buffer[(self->input_idx + i) % self->size] = buffer[i];
      i++;
    }
  self->counter += (size_t)ret;
  self->input_idx = self->input_idx + i;
  if (self->counter < self->size)
    self->input_idx %= self->size;
  return (true);
}
