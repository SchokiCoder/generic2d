/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2023  Andy Frank Schoknecht
 */

/*
#include "world.h"
#include "entity.h"

// TODO how to know which blocks are solid ?
// block data is defined by user
SM_bool Entity_move(Entity * ent, float *pos, float *velocity, float distance,
		    World * world)
{
	SM_bool collision = SM_FALSE;
	int_fast32_t x1, y1, x2, y2;
	FRect block_hitbox;

	// set position
	*pos += distance;

	// calculate which blocks to check
	x1 = ent->rect.x / world->block_size;
	y1 = ent->rect.y / world->block_size;
	x2 = (ent->rect.x + wldent->rect.w) / world->block_size + 1;
	y2 = (ent->rect.y + wldent->rect.h) / world->block_size + 1;

	// cap check-range to be within bounds
	if (x1 < 0)
		x1 = 0;

	if (x1 > (int_fast32_t) world->width - 1)
		x1 = (int_fast32_t) world->width - 1;

	if (y1 < 0)
		y1 = 0;

	if (y1 > (int_fast32_t) world->height - 1)
		y1 = (int_fast32_t) world->height - 1;

	if (x2 < 0)
		x2 = 0;

	if (x2 > (int_fast32_t) world->width - 1)
		x2 = (int_fast32_t) world->width - 1;

	if (y2 < 0)
		y2 = 0;

	if (y2 > (int_fast32_t) world->height - 1)
		y2 = (int_fast32_t) world->height - 1;

	// collision check within check-range
	block_hitbox.w = world->block_size;
	block_hitbox.h = world->block_size;

	for (int_fast32_t x = x1; x <= x2; x++) {
		for (int_fast32_t y = y1; y <= y2; y++) {
			// if non-solid block here, skip
			if (world->blocks[x][y] == B_NONE)
				continue;

			block_hitbox.x = x * world->block_size;
			block_hitbox.y = y * world->block_size;

			// if collision
			if (box_within_box(&ent->rect, &block_hitbox)) {
				// flag, reset pos, kill velocity
				collision = SM_TRUE;
				*pos -= distance;
				*velocity = 0.0f;
			}
		}
	}

	return collision;
}
*/

