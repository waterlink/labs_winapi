/*
 * mainform.cpp
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
 
#include "mainform.hpp"
#include "explore.hpp"
#include "controls.h"
#include "__task.hpp"
#include <cstdio>
#include <commctrl.h>

#include <algorithm>
#include <vector>
#include <string>

using namespace std;

#define maxcount 1000

windowhandle handle;
windowhandle mainview;
instancehandle instance;

char buff[maxcount];

char ** taskstring;

int initmainwindow(instancehandle instance, int showmode){ 

	windowclass mainwindow;

	mainwindow.style = horizontalverticalrepaint;
	mainwindow.lpfnWndProc = maindispatcher;
	mainwindow.cbClsExtra = 0;
	mainwindow.cbWndExtra = 0;
	mainwindow.hInstance = instance;
	mainwindow.hIcon = LoadIcon(0, standardicon);
	mainwindow.hCursor = LoadCursor(0, standardcursor);
	mainwindow.hbrBackground = (brushhandle)COLOR_WINDOW;
	mainwindow.lpszMenuName = "mainmenu";
	mainwindow.lpszClassName = "mainwindowclass";

	if (!RegisterClass(&mainwindow)) return 0;

	handle = CreateWindow("mainwindowclass", "Main Window", overlappedwindow, 
			50, 50, 400, 500,
			0, 0, instance, 0);
	if (!handle) return 0;
	
	ShowWindow(handle, showmode);
	UpdateWindow(handle);

	::instance = instance;
	
	mainview = CreateWindow(WC_LISTVIEW, "", LVS_SINGLESEL | LVS_EX_TWOCLICKACTIVATE | WS_BORDER | WS_VISIBLE | WS_CHILD, 
				50, 50, 300, 400, handle, (HMENU)lvMainView, instance, 0);

	return 1;

}
windowhandle getmainhandle(){ return handle; }
dispatcher maindispatcher(windowhandle handle, uint message, wparameter wparam, lparameter lparam){

	if (message == closemessage){

		PostQuitMessage(0);
		return 0;

	}
	
	vector < string > chosen;
	LVITEM newitem;
	string mbmes = "";

	dispatchstart(message, {

		gooddispatch(menuselectmessage, {

			if (getid(wparam) == mtest){

				// here Test dispatching
				DialogBox(::instance, getexplorename(), getmainhandle(), exploredispatcher);
				fprintf(stderr, "after OK\n");
				if (exploresuccess()){
				
					chosen = getexploreresult();
					ListView_DeleteAllItems(mainview);
					for (int i = chosen.size() - 1; i >= max(0, (int)chosen.size() - 5); --i){
					
						strcpy(buff, chosen[i].c_str());
						newitem.mask = LVIF_TEXT;
						newitem.pszText = buff;
						newitem.iItem = chosen.size() - 1 - i;
						newitem.iSubItem = 0;
						ListView_InsertItem(mainview, &newitem);
					
					}
				
				}

			}
			else if (getid(wparam) == mabout){
			
				taskstring = gettaskstring();
				for (int i = 1; strlen(taskstring[i]) > 0; ++i)
					mbmes = mbmes + taskstring[i] + "\n";
				MessageBox(NULL, mbmes.c_str(), "About", MB_OK);
			
			}
				
		})

	})

	return DefWindowProc(handle, message, wparam, lparam);

}



