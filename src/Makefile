# A program for verifying file integrity.
# Copyright (C) 2012 Vinny Diehl
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.

# @file Makefile - Contains instructions for building Checksum Finder.
#
# make
# Builds application.
#
# make debug
# Builds application with debugging symbols and DEBUG defined.
#
# make rebuild
# Rebuilds the application, including all object files.
#
# make rebuild-dbg
# Rebuilds the application, including all object files, to the debug target.
#
# make clean
# Deletes the object files.
#
# make erase
# make delete
# Deletes the bin/ and obj/ directories and all files within.

# Output Name
NAME = ChecksumFinder

# Set up debug target
# :TODO: 2012-05-27 gbchaosmaster - Get the debug target working.
# It is broken right now and does not build properly.
debug: TGT = debug

# Source Directories
INCDIR = Include
FRMDIR = Frames
CLSDIR = Classes

# wxWidgets Options
WXCFLAGS = -I/usr/lib/x86_64-linux-gnu/wx/include/gtk2-unicode-release-2.8 \
           -I/usr/include/wx-2.8 -D_FILE_OFFSET_BITS=64 -D_LARGE_FILES \
	   -D__WXGTK__
WXLFLAGS = -L/usr/lib/x86_64-linux-gnu -pthread -Wl,-Bsymbolic-functions \
           -Wl,-z,relro -L/usr/lib/x86_64-linux-gnu -lwx_gtk2u_richtext-2.8 \
	   -lwx_gtk2u_aui-2.8 -lwx_gtk2u_xrc-2.8 -lwx_gtk2u_qa-2.8 \
	   -lwx_gtk2u_html-2.8 -lwx_gtk2u_adv-2.8 -lwx_gtk2u_core-2.8 \
	   -lwx_baseu_xml-2.8 -lwx_baseu_net-2.8 -lwx_baseu-2.8

# Output Directories
BINROOT = bin
OBJROOT = obj

ifeq ($(TGT), debug)
    BINDIR = $(BINROOT)/Debug
    OBJDIR = $(OBJROOT)/Debug
else
    BINDIR = $(BINROOT)/Release
    OBJDIR = $(OBJROOT)/Release
endif

# Output Files
OBJ = Program.o frmMain.o MD5.o Clipboard.o
EXE = $(BINDIR)/$(NAME)
OPATHS = $(addprefix $(OBJDIR)/,$(OBJ))

# Compiler
CC = g++
DEBUG = -g -DDEBUG
CFLAGS = -Wall -c -o $@ $(WXCFLAGS) -I$(INCDIR)
LFLAGS = -Wall $(WXLFLAGS) -I$(INCDIR)

.PHONY: all debug configure clean rebuild rebuild-dbg erase delete

all: CFLAGS += -O2
all: LFLAGS += -O2
all: $(EXE)

debug: CFLAGS += $(DEBUG)
debug: LFLAGS += $(DEBUG)
debug: $(EXE)

$(EXE): configure $(OPATHS)
	$(CC) $(OPATHS) $(LFLAGS) -o $@

configure:
	mkdir -p $(BINDIR) $(OBJDIR)

$(OBJDIR)/Program.o: $(INCDIR)/Program.h $(INCDIR)/frmMain.h
	$(CC) $(CFLAGS) Program.cpp

$(OBJDIR)/frmMain.o: $(INCDIR)/frmMain.h
	$(CC) $(CFLAGS) $(FRMDIR)/frmMain.cpp

$(OBJDIR)/MD5.o: $(INCDIR)/MD5.h
	$(CC) $(CFLAGS) $(CLSDIR)/MD5.cpp

$(OBJDIR)/Clipboard.o: $(INCDIR)/Clipboard.h
	$(CC) $(CFLAGS) $(CLSDIR)/Clipboard.cpp

clean:
	mkdir -p $(OBJDIR) && rm -r $(OBJDIR)

rebuild: clean
rebuild: $(EXE)

rebuild-dbg: clean
rebuild-dbg: debug

erase: delete
delete:
	mkdir -p $(BINROOT) && rm -r $(BINROOT)
	mkdir -p $(OBJROOT) && rm -r $(OBJROOT)

