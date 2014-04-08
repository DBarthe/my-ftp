/*
** socket.h for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/common
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Tue Apr  8 18:49:54 2014 Barthelemy Delemotte
** Last update Tue Apr  8 19:02:52 2014 Barthelemy Delemotte
*/

#ifndef			SOCKET_H_
# define		SOCKET_H_

# include		<sys/types.h>
# include		<stdbool.h>

bool			send_str(int socket_fd, const char *str);
bool			send_raw(int socket_fd, const char *buffer,
				 size_t size);
bool			send_fmt(int socket_fd, const char *fmt, ...);

#endif			/* !SOCKET_H_ */
