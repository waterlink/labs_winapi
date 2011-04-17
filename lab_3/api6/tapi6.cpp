
#include "tapi6.hpp"

#include <windows.h>
#include <commctrl.h>
#include "menu.h"
#include <cstdio>


char* pMessages[]=
{
"Enable or disable exit",
"Exit from the program",
"About this program",
"File operations",
"Help operations",
"Menu example",
"System menu"
};

long WINAPI DepartComTechWndProc(HWND,UINT,UINT,LONG);

HWND hStatusWindow;
UINT wId;
HMENU hMenu,hFileMenu,hHelpMenu;
HINSTANCE hInst;

int APIENTRY WinMain(HINSTANCE hInstance, 
					HINSTANCE hPrevInstance,
				LPSTR lpszCmdParam, int nCmdShow)
{

HWND hWnd; 
WNDCLASS WndClass; 
MSG Msg;
HACCEL hAccel1, hAccel2, hAccel3, hAccel4;
hInst=hInstance;

// инициализация имени класса как строки

WndClass.style=CS_HREDRAW|CS_VREDRAW;
WndClass.lpfnWndProc=(WNDPROC)DepartComTechWndProc;
WndClass.cbClsExtra=0;
WndClass.cbWndExtra=0;
WndClass.hInstance=hInstance;
WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
WndClass.hbrBackground=(HBRUSH) GetStockObject(WHITE_BRUSH);
WndClass.lpszMenuName="MyMenu";
WndClass.lpszClassName="DepartComTech_Menu";

if(!RegisterClass(&WndClass))
{
	MessageBox(NULL,"Cannot register class","Error",MB_OK);
	return 0;
}

hWnd=CreateWindow("DepartComTech_Menu","Sixth Example",
				WS_OVERLAPPEDWINDOW, 
				CW_USEDEFAULT,CW_USEDEFAULT,
				CW_USEDEFAULT,CW_USEDEFAULT,
				NULL,NULL,
				hInstance,NULL);

if(!hWnd)

{
	MessageBox(NULL,"Cannot create window","Error",MB_OK);
	return 0;
}
//
InitCommonControls();
hStatusWindow=CreateStatusWindow(WS_CHILD|WS_VISIBLE,
								 NULL,hWnd,wId);

if(!hStatusWindow)

{
	MessageBox(NULL,"Cannot create status window",
		"Error",MB_OK);
	return 0;
}

//загрузка таблицы акселераторов
hAccel1=LoadAccelerators(hInst,"MyAccelerators");
/*hAccel2=LoadAccelerators(hInst,"EX");
hAccel3=LoadAccelerators(hInst,"ABO");
hAccel4=LoadAccelerators(hInst,"DISEN");*/

if (hAccel1 == NULL/* || hAccel2 == NULL || hAccel3 == NULL || hAccel4 == NULL */){

	printf("can't load acc\n");

}

//отобразить окно		   
ShowWindow(hWnd,nCmdShow);
UpdateWindow(hWnd);

hFileMenu=GetSubMenu(GetMenu(hWnd),0);

while(GetMessage(&Msg,NULL,0,0))
{
	if(!TranslateAccelerator(hWnd,hAccel1,&Msg))
	{
		TranslateMessage(&Msg);
	}
	DispatchMessage(&Msg);
}
return Msg.wParam;
}

long WINAPI DepartComTechWndProc(HWND hWnd,
				UINT Message, UINT wParam,LONG lParam)

{
RECT Rect;
static UINT nFlag=MF_ENABLED;

char* pContent[]=
{
"&Enable exit\te",
"&Disable exit\td"

};
static UINT nIndex=0;
switch(Message)
{
case WM_SYSCOMMAND:
	printf("%d %d %d %d\n", LOWORD(wParam), IDM_Exit, IDM_About, IDM_Enable_Disable);
	break;
case WM_COMMAND:
	printf("%d %d %d %d\n", LOWORD(wParam), IDM_Exit, IDM_About, IDM_Enable_Disable);
	switch(LOWORD(wParam))
	{
	case IDM_Enable_Disable:
		EnableMenuItem(hFileMenu, IDM_Exit, MF_BYCOMMAND|nFlag);
		nFlag=(nFlag==MF_ENABLED)? MF_GRAYED:MF_ENABLED;
		nIndex=(nIndex==0)?1:0;
		ModifyMenu(hFileMenu,IDM_Enable_Disable,
			MF_BYCOMMAND|MF_STRING,IDM_Enable_Disable,
			pContent[nIndex]);

	break;

	case IDM_Exit:
		SendMessage(hWnd,WM_CLOSE,NULL,NULL);
	break;
	}
case WM_SIZE:
	SendMessage(hStatusWindow,WM_SIZE,wParam,lParam);
	GetClientRect(hWnd,&Rect);
	return 0;
//
case WM_MENUSELECT:
	printf("%d %d %d\n", LOWORD(wParam), HIWORD(wParam), MF_POPUP);
	if(((UINT)HIWORD(wParam)==0xffff)&
		((HMENU)lParam==0))
	{
	SendMessage(hStatusWindow,SB_SETTEXT,(WPARAM) 0,
		(LPARAM) pMessages[5]);
	return 0;
	}
	if((UINT)HIWORD(wParam)& MF_SYSMENU)
	{
	SendMessage(hStatusWindow,SB_SETTEXT,(WPARAM) 0,
		(LPARAM) pMessages[6]);
	return 0;
	}
	if((UINT)HIWORD(wParam)& MF_POPUP)
	{
	SendMessage(hStatusWindow,SB_SETTEXT,(WPARAM) 0,
		(LPARAM) pMessages[3 + LOWORD(wParam)]);
	return 0;
	}
	SendMessage(hStatusWindow,SB_SETTEXT,(WPARAM) 0,
		(LPARAM) pMessages[LOWORD(wParam) - IDM_Enable_Disable]);
	return 0;
case WM_DESTROY:

	PostQuitMessage(0);
	return 0;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
return DefWindowProc(hWnd,Message,wParam,lParam);
}


