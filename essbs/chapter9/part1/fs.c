/*
fs.c:
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

#include "string.h"

#define MAX_SUPER_BLOCK 8
#define NULL (void *)0

struct super_block *fs_type[MAX_SUPER_BLOCK];


int register_file_system(struct super_block *type,unsigned int id){
	if(fs_type[id]==NULL){
		fs_type[id]=type;
		return 0;
	}
	return -1;
}

void unregister_file_system(struct super_block *type,unsigned int id){
	fs_type[id]=NULL;
}
