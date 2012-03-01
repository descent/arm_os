/*
fs.h:
Copyright (C) 2009  david leels <davidontech@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see http://www.gnu.org/licenses/.
*/

#include "storage.h"

#define MAX_SUPER_BLOCK	(8)

#define ROMFS	0

struct super_block;


struct inode{
	char *name;
	unsigned int flags;
	size_t dsize;			//file data size
	unsigned int daddr;				//real data bias inside the block device
	struct super_block *super;
	
};

struct super_block{
	struct inode *(*namei)(struct super_block *super,char *p);
	unsigned int (*get_daddr)(struct inode *);
	
	struct storage_device *device;
	char *name;
};

extern struct super_block *fs_type[];
