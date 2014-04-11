/*
** utils.h for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/serv
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Tue Apr  8 15:03:10 2014 Barthelemy Delemotte
** Last update Fri Apr 11 21:32:21 2014 Barthelemy Delemotte
*/

#ifndef		UTILS_H_
# define	UTILS_H_

void		die(const char *message);
void		diep(const char *prefix);
void		dief(const char *fmt, ...);
char		**my_str_to_wordtab(const char *str);

#endif		/* !UTILS_H_ */
