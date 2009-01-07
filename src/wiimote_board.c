/* $Id$ 
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

#include <stdio.h>
#include <stdlib.h>

#include "wiimote.h"
#include "wiimote_io.h"
#include "wiimote_error.h"
#include "wiimote_board.h"
#include "wiimote_event.h"

#define CLASSIC_MEM_START	0x04a40000
#define CLASSIC_MEM_END		0x04a400ff
#define CLASSIC_REG_CTRL	0x04a40040

#define board_decode_byte(x)	(((x) ^ 0x17) + 0x17)

int wiimote_board_enable(wiimote_t *wiimote, uint8_t enable)
{
	if (wiimote_write_byte(wiimote, CLASSIC_REG_CTRL, enable ? 0x00 : 0xff) < 0) {
		wiimote_error("wiimote_board_enable(): unable to write board");
		return WIIMOTE_ERROR;
	}
	return WIIMOTE_OK;
}

int wiimote_board_init(wiimote_t *wiimote)
{
	if (wiimote_board_enable(wiimote, 1) < 0) {
		wiimote_error("wiimote_board_init(): unable to initialize board controller");
		return WIIMOTE_ERROR;
	}
	
	return WIIMOTE_OK;
}

void wiimote_board_decode(uint8_t *data, uint32_t size)
{
	int i;
	for (i=0; i<size; i++) {
		data[i] = board_decode_byte(data[i]);
	}
}

int wiimote_board_update(wiimote_t *wiimote, uint8_t *data)
{
	return 0;
}
