/*
 * explore.cpp
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
 
#include "explore.hpp"
#include <commctrl.h>
#include "controls.h"

#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

#define maxcount 1000

instancehandle instance0;

bool dialogresult = false;
vector < string > chosenvector;

char * rootkeys[] = {

	"HKEY_CLASSES_ROOT/",
	"HKEY_CURRENT_CONFIG/",
	"HKEY_CURRENT_USER/",
	"HKEY_LOCAL_MACHINE/",
	"HKEY_PERFORMANCE_DATA/",
	"HKEY_USERS/"

};

string currkeys[maxcount];
string currway = "/";

int countrootkeys = 6;
int currcount = 0;

HKEY roothkeys[] = {

	HKEY_CLASSES_ROOT,
	HKEY_CURRENT_CONFIG,
	HKEY_CURRENT_USER,
	HKEY_LOCAL_MACHINE,
	HKEY_PERFORMANCE_DATA,
	HKEY_USERS

};

HKEY currentkey;
vector < HKEY > recursivekeys;

char buffer[maxcount];
DWORD bufflen;

int chosencount = 0;

set < string > chosenset;
map < int, string > chosenmap;

string decodeway(string way){

	string res = "";
	for (int i = 1; i < way.size(); ++i){

		if (way[i] == '/')
			res = res + '\\';
		else res = res + way[i];

	}
	return res;

}

string goback(string way){

	int i;
	string res = "";
	if (way.size() > 1){
	
		for (i = way.size() - 2; i > 0 && way[i] != '/'; --i) ;
		for (int j = 0; j <= i; ++j)
			res.push_back(way[j]);
		
	}
	return res;

}

void setup(instancehandle instance0){ ::instance0 = instance0; }
char * getexplorename(){ return "exploredialog"; }
vector < string > getexploreresult(){ return chosenvector; }
dialogdispatcher exploredispatcher(windowhandle dialog, uint message, wparameter wparam, lparameter lparam){

	if (message == preclosemessage){

		// do cleaning here
		dialogresult = false;
		for (int i = recursivekeys.size() - 1; i >= 0; --i)
			RegCloseKey(recursivekeys[i]);
		EndDialog(dialog, 0);
		return true;

	}

	windowhandle View;
	windowhandle Chosen;
	LVITEM newitem;
	LPNMITEMACTIVATE chosenitem;
	int index, len;
	DWORD subkeycount, valuescount;
	HKEY newkey;
	bool frecadd;
	string choice;
	LVFINDINFO itemtofind;

	dispatchstart(message, {

		gooddispatch(dialoginitmessage, {

			View = GetDlgItem(dialog, lvView);
			ListView_DeleteAllItems(View);
			for (int i = 0; i < countrootkeys; ++i){

				newitem.mask = LVIF_TEXT;
				newitem.pszText = rootkeys[i];
				newitem.iItem = i;
				newitem.iSubItem = 0;
				currkeys[i] = rootkeys[i];
				ListView_InsertItem(View, &newitem);

			}
			currcount = countrootkeys;
			currway = "/";
			SetDlgItemText(dialog, lblWay, currway.c_str());
			recursivekeys.clear();

		})

		gooddispatch(notifymessage, {
		
			//fprintf(stderr, "command message\n");

			if (getid(wparam) == lvView){
			
				//fprintf(stderr, "list view command message %d\n", getoption(wparam));
				
				chosenitem = (LPNMITEMACTIVATE)lparam;

				if (chosenitem->hdr.code == listviewactivatenotification){

					//fprintf(stderr, "list view activate notification\n");
					
					index = chosenitem->iItem;
					if (index >= 0 && index < currcount){

						if (currkeys[index][currkeys[index].size() - 1] == '/'){

							// go to new key
							frecadd = true;
							if (currkeys[index] == "../"){
						
								newkey = currentkey;
								currway = goback(currway);
								RegCloseKey(newkey);
								recursivekeys.pop_back();
								if (recursivekeys.size() > 0){
							
									currentkey = recursivekeys[recursivekeys.size() - 1];
									frecadd = false;
								
								}
								else{ 
							
									View = GetDlgItem(dialog, lvView);
									ListView_DeleteAllItems(View);
									for (int i = 0; i < countrootkeys; ++i){

										newitem.mask = LVIF_TEXT;
										newitem.pszText = rootkeys[i];
										newitem.iItem = i;
										newitem.iSubItem = 0;
										currkeys[i] = rootkeys[i];
										ListView_InsertItem(View, &newitem);

									}
									currcount = countrootkeys;
									currway = "/";
									currentkey = 0;
									SetDlgItemText(dialog, lblWay, currway.c_str());
									break;
								
								}
						
							}
							else if (currway == "/"){

								currentkey = roothkeys[index];

							}
							else {

								strcpy(buffer, currkeys[index].c_str());
								buffer[strlen(buffer) - 1] = 0;
								RegOpenKey(currentkey, buffer, &newkey);
								currentkey = newkey;

							}
							if (frecadd) recursivekeys.push_back(currentkey);
							fprintf(stderr, "recursivekeys size: %d\n", recursivekeys.size());
							View = GetDlgItem(dialog, lvView);
							ListView_DeleteAllItems(View);
							int err = RegQueryInfoKey(currentkey, 0, 0, 0, &subkeycount, 0, 0, &valuescount, 0, 0, 0, 0);
							if (!err){
							
								if (frecadd) currway = currway + currkeys[index];
								SetDlgItemText(dialog, lblWay, currway.c_str());
								currkeys[0] = "../";
								strcpy(buffer, currkeys[0].c_str());
								newitem.mask = LVIF_TEXT;
								newitem.pszText = buffer;
								newitem.iItem = 0;
								newitem.iSubItem = 0;
								ListView_InsertItem(View, &newitem);
								currcount = subkeycount + valuescount + 1;
								for (int i = 0; i < subkeycount; ++i){
								
									RegEnumKey(currentkey, i, buffer, maxcount);
									//buffer[bufflen] = 0;
									len = strlen(buffer);
									buffer[len] = '/';
									buffer[len + 1] = 0;
									currkeys[i + 1] = buffer;
									//currway = currway + currkeys[i + 1];
									newitem.mask = LVIF_TEXT;
									newitem.pszText = buffer;
									newitem.iItem = i + 1;
									newitem.iSubItem = 0;
									ListView_InsertItem(View, &newitem);
								
								}
								for (int i = 0; i < valuescount; ++i){
								
									bufflen = maxcount;
									RegEnumValue(currentkey, i, buffer, &bufflen, 0, 0, 0, 0);
									len = strlen(buffer);
									currkeys[1 + subkeycount + i] = buffer;
									newitem.mask = LVIF_TEXT;
									newitem.pszText = buffer;
									newitem.iItem = i + 1;
									newitem.iSubItem = 0;
									ListView_InsertItem(View, &newitem);
								
								}
							
							}

						}
						else{

							// add value
							View = GetDlgItem(dialog, lvView);
							Chosen = GetDlgItem(dialog, lvChosen);
							choice = currkeys[index] + " | " + currway + currkeys[index];
							//chosencount = chosenset.size();
							//chosenset.insert(choice);
							strcpy(buffer, choice.c_str());
							itemtofind.flags = LVFI_STRING;
							itemtofind.psz = buffer;
							if (ListView_FindItem(Chosen, -1, &itemtofind) == -1){

								//chosenmap[chosencount] = choice;
								chosencount++;
								newitem.mask = LVIF_TEXT;
								newitem.pszText = buffer;
								newitem.iItem = 0;
								newitem.iSubItem = 0;
								ListView_InsertItem(Chosen, &newitem);
								return true;
								
							}

						}

					}

				}

			}
			else if (getid(wparam) == lvChosen){
			
				Chosen = GetDlgItem(dialog, lvChosen);
				chosenitem = (LPNMITEMACTIVATE)lparam;
				if (chosenitem->hdr.code == listviewactivatenotification){
				
					index = chosenitem->iItem;
					if (index >= 0 && index < chosencount){
					
						//choice = chosenmap[index];
						//chosenset.erase(choice);
						--chosencount;
						ListView_DeleteItem(Chosen, index);
						return true;

					}
				
				}
			
			}

		})
		gooddispatch(commandmessage, {
		
			if (getid(wparam) == btnOk){
				
				Chosen = GetDlgItem(dialog, lvChosen);
				chosenvector.clear();
				chosencount = ListView_GetItemCount(Chosen);
				for (int i = 0; i < chosencount; ++i){
				
					ListView_GetItemText(Chosen, i, 0, buffer, maxcount);
					choice = buffer;
					if (choice != "")
						chosenvector.push_back(choice);
				
				}
				
				fprintf(stderr, "OK\n");
				dialogresult = true;
				for (int i = recursivekeys.size() - 1; i >= 0; --i)
					RegCloseKey(recursivekeys[i]);
				EndDialog(dialog, 0);
				return true;
			
			}
			else if (getid(wparam) == btnCancel){
			
				dialogresult = false;
				for (int i = recursivekeys.size() - 1; i >= 0; --i)
					RegCloseKey(recursivekeys[i]);
				EndDialog(dialog, 0);
				return true;
			
			}
		
		})

	})

	return false;

}
bool exploresuccess(){ return dialogresult; }


