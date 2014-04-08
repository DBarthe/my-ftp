/*
** defines.h for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/serv
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Tue Apr  8 15:04:17 2014 Barthelemy Delemotte
** Last update Tue Apr  8 15:17:04 2014 Barthelemy Delemotte
*/

#ifndef		DEFINES_H_
# define	DEFINES_H_

# define	RET_SUCCESS	0
# define	RET_FAILURE	1
# define	RET_ERROR	-1

# ifdef		DEBUG
#  define	IFDEBUG(instr)	instr
#  define	IFNDEBUG(instr)
#  include	<stdio.h>
# else
#  define	IFDEBUG(instr)
#  define	IFNDEBUG(instr)	instr
# endif		/* DEBUG */

# define	DEBUG_PRINT(s)	IFDEBUG(printf("#INFO: %s\n", s))

#endif		/* !DEFINES_H_ */
