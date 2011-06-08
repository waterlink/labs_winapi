/*
 * x.cpp
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
	TASK 2:
		- go to disk A
		- create your own directory
		- create your own anketa-file int your own directory
		- fill anketa up
*/
 


#include <windows.h>

int __stdcall WinMain(HINSTANCE Inst, HINSTANCE, char * arg, int mode){

	SetCurrentDirectory("a:\\");
	CreateDirectory("FedorovAK_anketa", 0);
	SetCurrentDirectory(".\\FedorovAK_anketa\\");
	HANDLE myfile = CreateFile(
			"FedorovAK.ank",
			GENERIC_READ|GENERIC_WRITE,
			FILE_SHARE_READ|FILE_SHARE_WRITE,
			NULL,
			CREATE_NEW,
			FILE_ATTRIBUTE_NORMAL,
			0
		);
	char buffer[] = "Fedorov\nAlexey\nKonstantinovich\nISPR-A1\nDonNU-PhysFac\n";
	WriteFile(myfile, (LPCVOID)buffer, (DWORD)strlen(buffer), 0, 0);
	CloseHandle(myfile);

	return 0;

}


