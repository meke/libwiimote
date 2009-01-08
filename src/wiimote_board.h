/* $Id: wiimote_board.h 51 2007-03-10 14:36:44Z bja $ 
 *
 * Copyright (C) 2007, Joel Andersson <bja@kth.se>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */
 
#ifndef _BOARD_H_
#define _BOARD_H_

#include "wiimote.h"

#define WIIMOTE_BOARD_ID  0x04
#define board_decode_byte(x)	(((x) ^ 0x17) + 0x17)

int board_init(wiimote_t *wiimote);
int board_update(wiimote_t *wiimote);
int board_free(wiimote_t *wiimote);
void board_decode(uint8_t *data, uint32_t size);
int board_enable(wiimote_t *wiimote, uint8_t enable);

#endif /* _BOARD_H_ */
