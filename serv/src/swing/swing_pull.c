/*
** swing_pull.c for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/serv/src
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Tue Apr  8 17:43:14 2014 Barthelemy Delemotte
** Last update Tue Apr  8 17:43:58 2014 Barthelemy Delemotte
*/

#include		<unistd.h>
#include		<stdlib.h>
#include		<string.h>

#include		"swing.h"
#include		"utils.h"
#include		"defines.h"

char			*swing_pull_cmd(t_swing *self)
{
  char			*cmd;
  size_t		cmd_size;
  size_t		i;

  cmd_size = 0;
  while (cmd_size < self->counter)
    {
      if (self->buffer[(self->output_idx + cmd_size) % self->size] == END_OF_CMD)
	break;
      cmd_size++;
    }
  if ((cmd = malloc((cmd_size + 1) * sizeof(char))) == NULL)
    die("malloc has failed");
  i = 0;
  while (i < cmd_size)
    {
      cmd[i] = self->buffer[(self->output_idx + i) % self->size];
      i++;
    }
  cmd[i] = '\0';
  self->counter -= cmd_size + 1;
  self->output_idx = self->output_idx + cmd_size + 1;
  if (self->counter < self->size)
    self->output_idx %= self->size;
  return (cmd);
}

char			*swing_pull_rest(t_swing *self, size_t *size)
{
  char			*rest;
  size_t		i;

  *size = self->counter;
  if (self->counter == 0)
    return (NULL);
  if ((rest = malloc((self->counter + 1) * sizeof(char))) == NULL)
    die("malloc has failed");
  i = 0;
  while (i < self->counter)
    {
      rest[i] = self->buffer[(self->output_idx + i) % self->size];
      i++;
    }
  rest[i] = '\0';
  self->counter = 0;
  self->output_idx += i;
  return (rest);
}
