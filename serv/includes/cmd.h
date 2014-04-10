/*
** cmd.h for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/serv/src/cmd
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Wed Apr  9 15:12:18 2014 Barthelemy Delemotte
** Last update Thu Apr 10 13:29:54 2014 Barthelemy Delemotte
*/

#ifndef			CMD_H_
# define		CMD_H_

# include		<stdbool.h>

# include		"session.h"

# define		CMD_IS_SEP(c)	((c) == ' ' || (c) == '\t')
# define		CMD_IS_INHIB(c)	((c) == '\'' || (c) == '\"')

typedef	struct
{
  char			*raw;
  const char		*name;
  const char		*arg;
}			t_cmd;

bool			cmd_parse(t_cmd *self, char *raw, t_session *session);
bool			cmd_exec(t_cmd *self, t_session *session);
void			cmd_clean(t_cmd *self);
void			cmd_dump(const t_cmd *self);
bool			cmd_exec_system(const char *cmd, t_session *session);
bool			cmd_exec_ls(t_cmd *self, t_session *session);
bool			cmd_exec_cd(t_cmd *self, t_session *session);
bool			cmd_exec_pwd(t_cmd *self, t_session *session);
bool			cmd_exec_quit(t_cmd *self, t_session *session);

#endif			/* !CMD_H_ */
