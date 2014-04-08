/*
** session.h for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/serv/src
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Tue Apr  8 17:53:03 2014 Barthelemy Delemotte
** Last update Tue Apr  8 18:41:24 2014 Barthelemy Delemotte
*/

#ifndef			SESSION_H_
# define		SESSION_H_

# include		<stdbool.h>

# include		"swing.h"

typedef	struct
{
  int			fd;
  t_swing		swing;
  bool			quit;
}			t_session;

void			session_ctor(t_session *self, int cli_fd);
void			session_dtor(t_session *self);
void			session_run(t_session *self);

#endif			/* !SESSION_H_ */