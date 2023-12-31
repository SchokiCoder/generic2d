/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2023  Andy Frank Schoknecht
 */

#ifndef _ENTITY_H
#define _ENTITY_H

#include "types.h"

struct World;

struct EntityData {
	char *name;
	u32 width;
	u32 height;
	f32 acceleration;
	f32 max_velocity;
	f32 decceleration;
	f32 jump_velocity;
};

struct Entity {
	u32 id;
	struct FRect rect;
	f32 velocity_x, velocity_y;
	int grounded;
};

/*
// Moves the entity one dimension at a time.
SM_bool Entity_move(Entity * ent, f32 *pos, f32 *velocity, f32 distance,
		    World * world);
*/

#endif				/* _ENTITY_H */
