# SPDX-License-Identifier: GPL-2.0-or-later
# Copyright (C) 2023  Andy Frank Schoknecht

APP_NAME=2d
APP_VERSION=0.0.0
APP_LICENSE=GPL-2.0-or-later
APP_LICENSE_SOURCE1=You should have received a copy of the GNU General Public License along with this program;
APP_LICENSE_SOURCE2=if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
APP_SOURCE=https://github.com/SchokiCoder/generic2d

BIN_DIR=$(HOME)/.local/bin
TEXTURES_DIR=$(HOME)/.local/share/$(APP_NAME)/textures
WORLDS_DIR=$(HOME)/.local/share/$(APP_NAME)/worlds

DEFINES=-D PATH_TEXTURES="\"$(TEXTURES_DIR)/\"" \
	-D APP_NAME="\"$(APP_NAME)\"" \
	-D APP_VERSION="\"$(APP_VERSION)\"" \
	-D APP_LICENSE="\"$(APP_LICENSE)\"" \
	-D APP_LICENSE_SOURCE1="\"$(APP_LICENSE_SOURCE1)\"" \
	-D APP_LICENSE_SOURCE2="\"$(APP_LICENSE_SOURCE2)\"" \
	-D APP_SOURCE="\"$(APP_SOURCE)\""

CC=cc
INCLUDE=-I . -I /usr/include/SDL2
LIBS=-l SDL2 -l SDL2_ttf
CFLAGS=-std=c99 -Wall -Wextra $(INCLUDE) $(LIBS) $(DEFINES)
REL_CFLAGS=$(CFLAGS) -Os
DEB_CFLAGS=$(CFLAGS) -g -D _DEBUG #-fsanitize=address,undefined

TARGETS_GUI=gui/sprite.o \
	gui/entry.o \
	gui/button.o \
	gui/label.o \
	gui/menu.o

TARGETS_ENGINE=engine/dict.o \
	engine/sstring.o \
	engine/log.o \
	engine/physics.o \
	engine/world.o

TARGETS=$(TARGETS_ENGINE) $(TARGETS_GUI) \
	world.o path.o main.o game.o entity.o config.o

# compiles every module itself
2d: *.c engine/*.c gui/*.c
	$(CC) $(REL_CFLAGS) -o $@ $^

2d_d: *.c engine/*.c gui/*.c
	$(CC) $(DEB_CFLAGS) -o $@ $^

#2d_d: $(TARGETS)
#	$(CC) $(DEB_CFLAGS) -o $@ $^

config.o: config.c config.h
	$(CC) $(DEB_CFLAGS) -c -o $@ $<

entity.o: entity.c entity.h
	$(CC) $(DEB_CFLAGS) -c -o $@ $<

game.o: game.c game.h
	$(CC) $(DEB_CFLAGS) -c -o $@ $<

main.o: main.c
	$(CC) $(DEB_CFLAGS) -c -o $@ $<

path.o: path.c path.h
	$(CC) $(DEB_CFLAGS) -c -o $@ $<

world.o: world.c world.h
	$(CC) $(DEB_CFLAGS) -c -o $@ $<

gui/menu.o: gui/menu.c gui/menu.h
	$(CC) $(DEB_CFLAGS) -c -o $@ $<

gui/label.o: gui/label.c gui/label.h
	$(CC) $(DEB_CFLAGS) -c -o $@ $<

gui/button.o: gui/button.c gui/button.h
	$(CC) $(DEB_CFLAGS) -c -o $@ $<

gui/entry.o: gui/entry.c gui/entry.h
	$(CC) $(DEB_CFLAGS) -c -o $@ $<

gui/sprite.o: gui/sprite.c gui/sprite.h
	$(CC) $(DEB_CFLAGS) -c -o $@ $<

engine/world.o: engine/world.c engine/world.h
	$(CC) $(DEB_CFLAGS) -c -o $@ $<

engine/physics.o: engine/physics.c engine/physics.h
	$(CC) $(DEB_CFLAGS) -c -o $@ $<

engine/log.o: engine/log.c engine/log.h
	$(CC) $(DEB_CFLAGS) -c -o $@ $<

engine/sstring.o: engine/sstring.c engine/sstring.h
	$(CC) $(DEB_CFLAGS) -c -o $@ $<

engine/dict.o: engine/dict.c engine/dict.h
	$(CC) $(DEB_CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGETS)
	rm -f generic2d
	rm -f generic2d_d
