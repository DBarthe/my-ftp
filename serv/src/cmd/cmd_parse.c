/*
** cmd_parse.c for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/serv/src/cmd
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Wed Apr  9 15:32:48 2014 Barthelemy Delemotte
** Last update Wed Apr  9 16:56:22 2014 Barthelemy Delemotte
*/

#include		<stdlib.h>
#include		<string.h>
#include		<assert.h>

#include		"cmd.h"
#include		"socket.h"

static bool		token_sep(t_cmd *self, int i,
				  const char **word, char *inhib)
{
  if (*word && !*inhib)
    {
      self->raw[i] = '\0';
      return (true);
    }
  return (false);
}

static bool		token_inhib(t_cmd *self, int i,
				    const char **word, char *inhib)
{
  char			c;

  c = self->raw[i];
  if (*inhib == c)
    {
      self->raw[i] = '\0';
      *inhib = '\0';
      return (true);
    }
  else if (!*word && !*inhib)
    {
      *inhib = c;
      *word = &self->raw[i + 1];
    }
  return (false);
}

static bool		token_other(t_cmd *self, int i,
				    const char **word, char *inhib)
{
  (void)inhib;
  if (!*word)
    *word = &self->raw[i];
  return (false);
}

static bool		cmd_get_word(t_cmd *self, int i, const char **word,
				     t_session *session)
{
  char			inhib;
  bool			end;

  inhib = '\0';
  *word = NULL;
  end = false;
  while (!end && self->raw[i])
    {
      if (CMD_IS_SEP(self->raw[i]))
	end = token_sep(self, i, word, &inhib);
      else if (CMD_IS_INHIB(self->raw[i]))
	end = token_inhib(self, i, word, &inhib);
      else
	end = token_other(self, i, word, &inhib);
      i++;
    }
  if (inhib)
    {
      send_fmt(session->fd, "[ERROR] syntax: expected inhibitor '%c'\n",
	       inhib);
      *word = NULL;
      return (false);
    }
  return (true);
}

bool			cmd_parse(t_cmd *self, char *raw, t_session *session)
{
  size_t		len;
  size_t		arg_idx;

  self->raw = raw;
  self->name = NULL;
  self->arg = NULL;
  len = strlen(self->raw);
  if (!cmd_get_word(self, 0, &self->name, session) || !self->name)
    return (false);
  arg_idx = (self->name - self->raw) + strlen(self->name) + 1;
  if (arg_idx < len &&
      !cmd_get_word(self, (int)arg_idx, &self->arg, session))
    return (false);
  return (true);
}
