/*
 * mainform.hpp
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

#include "deffs.hpp"
#include <windows.h>

int initmainwindow(instancehandle instance, int showmode);
windowhandle getmainhandle();
dispatcher maindispatcher(windowhandle handle, uint message, wparameter wparam, lparameter lparam);



