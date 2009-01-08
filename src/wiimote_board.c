/* $Id: wiimote_board.c 53 2007-03-10 14:46:36Z bja $ 
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
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "wiimote.h"
#include "wiimote_error.h"
#include "wiimote_io.h"
#include "wiimote_board.h"

#define NUNCHUK_MEM_START	0x04a40000
#define NUNCHUK_MEM_END		0x04a400ff
#define NUNCHUK_REG_CTRL	0x04a40040
#define NUNCHUK_REG_CAL		0x04a40020

static int board_calibrate(wiimote_t *wiimote)
{
	/*
	uint8_t *data = (uint8_t *)&wiimote->ext.board.ctl;
	if (wiimote_read(wiimote, NUNCHUK_REG_CAL, data, sizeof (board_cal_t)) < 0) {		
		wiimote_set_error("board_calibrate(): unable to read calibration data");
		return WIIMOTE_ERROR;
	}
	*/
	return WIIMOTE_OK;
}

int board_enable(wiimote_t *wiimote, uint8_t enable)
{
	if (wiimote_write_byte(wiimote, NUNCHUK_REG_CTRL, enable ? 0x00 : 0xff) < 0) {
		wiimote_set_error("board_free(): unable to write board");
		return WIIMOTE_ERROR;
	}
	return WIIMOTE_OK;
}

int board_init(wiimote_t *wiimote)
{
	if (board_enable(wiimote, 1) < 0) {
		wiimote_set_error("board_init(): unable to initialize board");
		return WIIMOTE_ERROR;
	}
	
	if (board_calibrate(wiimote) < 0) {
		wiimote_set_error("board_init(): unable to calibrate board");
		return WIIMOTE_ERROR;
	}
	
	return WIIMOTE_OK;
}

int board_update(wiimote_t *wiimote)
{
	uint8_t data[16];
	
	if (wiimote_read(wiimote, NUNCHUK_MEM_START, data, 16) < 0) {
		wiimote_set_error("board_update(): unable to read board state: %s", wiimote_get_error());
		return WIIMOTE_ERROR;
	}
	
	board_decode(&data[8], 6);
		
	if (!memcpy((uint8_t*)&wiimote->ext.board, &data[8], 6)) {
		wiimote_set_error("board_update(): memcpy: %s", strerror(errno));
		return WIIMOTE_ERROR;
	}
	
	return WIIMOTE_OK;
}

void board_decode(uint8_t *data, uint32_t size)
{
	int i;
	for (i=0; i<size; i++) {
		data[i] = board_decode_byte(data[i]);
	}
}

int board_free(wiimote_t *wiimote)
{
	board_enable(wiimote, 0);
	
	/*
	if (memset(&wiimote->ext.board.cal, 0, sizeof (board_cal_t)) < 0) {
		wiimote_set_error("board_free(): unable to clear calibration data");
		return WIIMOTE_ERROR;
}
	*/
	return WIIMOTE_OK;
}


