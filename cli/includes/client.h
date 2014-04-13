/*
** client.h for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/cli/src
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Sun Apr 13 13:49:58 2014 Barthelemy Delemotte
** Last update Sun Apr 13 14:33:00 2014 Barthelemy Delemotte
*/

#ifndef			CLIENT_H_
# define		CLIENT_H_

int			setup(const char *hostname, int port_no);
void			run(int socket_fd);

#endif			/* !CLIENT_H_ */
