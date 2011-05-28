/*
 * deffs.hpp
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

#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0501

#undef _WIN32_IE
#define _WIN32_IE 0x0501

#define start WinMain
#define standardcall __stdcall
#define instancehandle HINSTANCE
#define windowhandle HWND
#define winmessage MSG
#define windowclass WNDCLASS
#define overlappedwindow WS_OVERLAPPEDWINDOW
#define dispatcher LRESULT CALLBACK
#define standardicon IDI_APPLICATION
#define standardcursor IDC_ARROW
#define uint UINT
#define lparameter LPARAM
#define wparameter WPARAM
#define brushhandle HBRUSH
#define hasowndevicecontext CS_OWNDC
#define defaultcoordinates CW_USEDEFAULT
#define horizontalverticalrepaint CS_HREDRAW | CS_VREDRAW
#define closemessage WM_DESTROY
#define preclosemessage WM_CLOSE
#define gooddispatch(message, x) case message: {x} break;
#define baddispatch(message, x) case message: {x}
#define menuselectmessage WM_MENUSELECT
#define getid(param) LOWORD(param)
#define getoption(param) HIWORD(param)
#define dispatchstart(message, x) switch(message){x}
#define dialogdispatcher BOOL CALLBACK
#define dialoginitmessage WM_INITDIALOG
#define commandmessage WM_COMMAND
#define listviewactivatenotification LVN_ITEMACTIVATE
#define notifymessage WM_NOTIFY


