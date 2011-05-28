/*
 * main.cpp
 * This file is part of winapi lab 4
 *
 * Copyright (C) 2011 - waterlink
 *
 * winapi lab 4 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * winapi lab 4 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with winapi lab 4; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 */
 
#include "main.hpp"
#include "mainform.hpp"
#include <cstdio>
#include <commctrl.h>

int standardcall start(instancehandle instance, instancehandle deprecated, char * parameters, int showmode){

	InitCommonControls();
	if (!initmainwindow(instance, showmode)){

		fprintf(stderr, "can't initialize main window\n");
		return 0;

	}

	return mainloop();

}

int mainloop(){

	winmessage message;
	int flag = 1;
	while (flag){

		int i = GetMessage(&message, 0, 0, 0);
		if (i == -1){

			// error handling
			flag = 0;

		}
		else if (i == 0){

			flag = 0;

		}
		else {

			TranslateMessage(&message);
			DispatchMessage(&message);

		}

	}

	return message.wParam;

}

