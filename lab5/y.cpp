/*
 * y.cpp
 * This file is part of lab 5
 *
 * Copyright (C) 2011 - waterlink Fedorov Alexey
 *
 * lab 5 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * lab 5 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with lab 5; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 */
 
/*
	TASK 3 Var 2
		- opens 2 desired files
		- compares thus timestamps
		- prints compare results and security attr
*/
 
#include <windows.h>
#include <cstdio>
#include <string>

using namespace std;

int __stdcall WinMain(HINSTANCE Inst, HINSTANCE, char * arg, int mode){

	string s1, s2;
	getline(cin, s1);
	getline(cin, s2);
	HANDLE f1 = CreateFile(
			s1.c_str(),
			GENERIC_READ|GENERIC_WRITE,
			FILE_SHARE_READ|FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			0
		);
	HANDLE f2 = CreateFile(
			s2.c_str(),
			GENERIC_READ|GENERIC_WRITE,
			FILE_SHARE_READ|FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			0
		);
		
	FILETIME ftc1, fta1, ftw1;
	FILETIME ftc2, fta2, ftw2;
	GetFileTime(f1, &ftc1, &fta1, &ftw1);
	GetFileTime(f2, &ftc2, &fta2, &ftw2);
	CloseFile(f1);
	CloseFile(f2);

	return 0;

}

