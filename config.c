/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2023  Andy Frank Schoknecht
 */

#include "config.h"
#include "engine/dict.h"
#include "engine/log.h"
#include "path.h"

struct Config Config_new(void)
{
	struct Config cfg = {
		.invalid = 0,
		.gfx_window_x = CFG_STD_GFX_WINDOW_X,
		.gfx_window_y = CFG_STD_GFX_WINDOW_Y,
		.gfx_window_w = CFG_STD_GFX_WINDOW_W,
		.gfx_window_h = CFG_STD_GFX_WINDOW_H,
		.gfx_window_fullscreen = CFG_STD_GFX_WINDOW_FULLSCREEN,
	};

	return cfg;
}

void Config_from_file(struct Config *cfg)
{
	const char *temp;
	struct String filepath = String_new(16);
	struct String msg = String_new(1);

	// get path
	if (get_config_path(&filepath) != 0) {
		String_clear(&filepath);
		cfg->invalid = 1;
		return;
	}
	// read file
	struct Dict dict = Dict_from_file(filepath.str);

	if (dict.invalid) {
		String_clear(&filepath);
		cfg->invalid = 1;
		log_warn("Config could not be loaded.");
		return;
	}
	// convert dict into config
	for (size_t i = 0; i < dict.len; i++) {
		// window pos, size
		if (strequal(dict.data[i].key.str, CFG_SETTING_GFX_WINDOW_X))
			cfg->gfx_window_x =
			    strtol(dict.data[i].value.str, NULL, 10);

		else if (strequal
			 (dict.data[i].key.str, CFG_SETTING_GFX_WINDOW_Y))
			cfg->gfx_window_y =
			    strtol(dict.data[i].value.str, NULL, 10);

		else if (strequal
			 (dict.data[i].key.str, CFG_SETTING_GFX_WINDOW_W))
			cfg->gfx_window_w =
			    strtol(dict.data[i].value.str, NULL, 10);

		else if (strequal
			 (dict.data[i].key.str, CFG_SETTING_GFX_WINDOW_H))
			cfg->gfx_window_h =
			    strtol(dict.data[i].value.str, NULL, 10);

		else if (strequal
			 (dict.data[i].key.str,
			  CFG_SETTING_GFX_WINDOW_FULLSCREEN))
			cfg->gfx_window_fullscreen =
			    strtol(dict.data[i].value.str, NULL, 10);

		// unknown option
		else {
			temp = "Unknown config setting \"";
			String_copy(&msg, temp, strlen(temp));
			String_append(&msg,
			              dict.data[i].key.str,
			              dict.data[i].key.len);
			temp = "\".";
			String_append(&msg, temp, strlen(temp));
			log_warn(msg.str);
		}
	}

	String_clear(&filepath);
	String_clear(&msg);
	Dict_clear(&dict);
}

void Config_to_file(struct Config *cfg)
{
	struct String filepath = String_new(16);

	/* get path */
	if (get_config_path(&filepath) != 0) {
		String_clear(&filepath);
		cfg->invalid = 1;
		return;
	}
	// convert config into dict
	struct Dict dict = Dict_new(1);
	char temp[10];

	sprintf(temp, "%i", cfg->gfx_window_x);
	Dict_add(&dict, CFG_SETTING_GFX_WINDOW_X, temp);
	sprintf(temp, "%i", cfg->gfx_window_y);
	Dict_add(&dict, CFG_SETTING_GFX_WINDOW_Y, temp);
	sprintf(temp, "%i", cfg->gfx_window_w);
	Dict_add(&dict, CFG_SETTING_GFX_WINDOW_W, temp);
	sprintf(temp, "%i", cfg->gfx_window_h);
	Dict_add(&dict, CFG_SETTING_GFX_WINDOW_H, temp);
	sprintf(temp, "%i", cfg->gfx_window_fullscreen);
	Dict_add(&dict, CFG_SETTING_GFX_WINDOW_FULLSCREEN, temp);

	// save
	if (!Dict_to_file(&dict, filepath.str))
		cfg->invalid = 1;

	// clear
	String_clear(&filepath);
	Dict_clear(&dict);
}
