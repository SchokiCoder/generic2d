/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2023  Andy Frank Schoknecht
 */

#ifndef _CH_PATH_H
#define _CH_PATH_H

#include "engine/sstring.h"
#include "engine/types.h"

#ifdef _WIN32
	#define SLASH "\\"
#else
	#define SLASH "/"
#endif /* _WIN32 */

static const char *PATH_WORLDS = "worlds";
static const char *PATH_CONFIG = "config.cfg";
//static const char *PATH_TEXTURE_ICON = PATH_TEXTURES "icon.png";

static const char *FILETYPE_WORLD = "wld";
//static const char *FILETYPE_BACKUP = "bkp";

i32 get_base_path(struct String *out);

i32 get_world_path(struct String *out);

i32 get_config_path(struct String *out);

int file_check_existence(const char *path);

#endif				/* _CH_PATH_H */
