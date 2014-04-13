/*
** swing.c for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/serv/src
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Tue Apr  8 16:36:07 2014 Barthelemy Delemotte
** Last update Sun Apr 13 14:21:52 2014 Barthelemy Delemotte
*/

#include		<unistd.h>
#include		<stdlib.h>
#include		<stdio.h>
#include		<string.h>

#include		"swing.h"
#include		"utils.h"
#include		"defines.h"

void			swing_ctor(t_swing *self)
{
  memset(self, 0, sizeof(*self));
  self->size = SWING_STARTING_SIZE;
  self->buffer = calloc(SWING_STARTING_SIZE, sizeof(char));
  if (self->buffer == NULL)
    die("malloc has failed");
}

void			swing_dtor(t_swing *self)
{
  free(self->buffer);
}


bool			swing_is_cmd_available(const t_swing *self)
{
  size_t		i;

  i = 0;
  while (i < self->counter)
    {
      if (self->buffer[(self->output_idx + i) % self->size] == END_OF_CMD)
	return (true);
      i++;
    }
  return (false);
}

void			swing_dump(const t_swing *self)
{
  size_t		i;

  printf("swing: size=%lu counter=%lu input_idx=%lu output_idx=%lu\n",
	 self->size, self->counter, self->input_idx, self->output_idx);
  printf("[");
  i = 0;
  while (i < self->counter)
    {
      printf("%c", self->buffer[(self->output_idx + i) % self->size]);
      i++;
    }
  printf("]\n");
}
