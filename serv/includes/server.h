/*
** server.h for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/serv
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Tue Apr  8 14:34:11 2014 Barthelemy Delemotte
** Last update Tue Apr  8 15:36:43 2014 Barthelemy Delemotte
*/

#ifndef			SERVER_H_
# define		SERVER_H_

# include		<stdint.h>

# define		SERVER_BACKLOG	50

typedef	void		(*t_accept_callback)(int);

typedef	struct
{
  int			socket_fd;
  t_accept_callback	callback;
}			t_server;

void			server_setup(t_server *self, uint16_t port,
				     t_accept_callback callback);
void			server_run(t_server *self);

#endif		/* SERVER_H_ */
