/*
** swing.h for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp/serv/src
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Tue Apr  8 16:19:22 2014 Barthelemy Delemotte
** Last update Sun Apr 13 13:36:41 2014 Barthelemy Delemotte
*/

#ifndef			SWING_H_
# define		SWING_H_

# include		<sys/types.h>
# include		<stdbool.h>

# define		SWING_STARTING_SIZE	512
# define		SWING_FEED_SIZE		128
# define		END_OF_CMD		'\n'

typedef	struct
{
  char			*buffer;
  size_t		size;
  size_t		input_idx;
  size_t		output_idx;
  size_t		counter;
}			t_swing;

void			swing_ctor(t_swing *self);
void			swing_dtor(t_swing *self);
bool			swing_feed(t_swing *self, int fd);
bool			swing_is_cmd_available(const t_swing *self);
char			*swing_pull_cmd(t_swing *self);
char			*swing_pull_rest(t_swing *self, size_t *size);
void			swing_dump(const t_swing *self);

#endif			/* !SWING_H_ */
