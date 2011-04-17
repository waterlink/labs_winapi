#include <windows.h>
#include <commctrl.h>
#include <cstdio>

// here error 1 was fixed
#define IDM_Enable_Disable 0
#define IDM_Exit 1
#define IDM_About 2
#define IDP_File 3
#define IDP_Help 4
#define IDM_Bitmap 5

char* pMessages[]=
{
"Enable or disable exit",
"Exit from the program",
"About this program",
"File operations",
"Help operations",
"Menu example",
"System menu",
"Shows specific action"
};

LRESULT CALLBACK DepartComTechWndProc(HWND,UINT,UINT,LONG);

HWND hStatusWindow;
UINT wId;
HMENU hMenu,hFileMenu,hHelpMenu;
HINSTANCE hInst;

int APIENTRY WinMain(HINSTANCE hInstance, 
					HINSTANCE hPrevInstance,
				LPSTR lpszCmdParam, int nCmdShow)
{

WNDCLASS WndClass; 
HWND hWnd; 
MSG Msg;

hInst=hInstance;
// инициализация имени класса как строки
//char szClassName[]="DepartComTech";

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

hWnd=CreateWindow("DepartComTech_Menu","Fifth Example",
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

//создание меню
//
AppendMenu((hFileMenu=CreatePopupMenu()),MF_ENABLED|
		   MF_STRING,IDM_Enable_Disable,
		   "&Enable exit");
AppendMenu(hFileMenu,MF_GRAYED| MF_STRING,IDM_Exit,
			"E&xit");
AppendMenu((hHelpMenu=CreatePopupMenu()),MF_DISABLED|
		   MF_STRING,IDM_About,
			"&About");
//
hMenu=CreateMenu();

AppendMenu(hMenu,MF_ENABLED|MF_POPUP,(UINT)hFileMenu,
			"&File");

AppendMenu(hMenu,MF_ENABLED|MF_POPUP,(UINT)hHelpMenu,
			"&Help");

// here seems to be fixed error 3
static HANDLE hBitmap;
int nDimension;

	nDimension=GetSystemMetrics(SM_CYMENUCHECK);
	hBitmap=LoadImage(hInst,"my.bmp", IMAGE_BITMAP,
	nDimension,nDimension,LR_LOADFROMFILE);
	AppendMenu(hMenu,MFT_BITMAP,IDM_Bitmap, (char *) hBitmap);



//
SetMenu(hWnd,hMenu);
//отобразить окно		   
ShowWindow(hWnd,nCmdShow);
UpdateWindow(hWnd);
//
DrawMenuBar(hWnd);

while(GetMessage(&Msg,NULL,0,0))
{
	TranslateMessage(&Msg);
	DispatchMessage(&Msg);
}
return Msg.wParam;
}

LRESULT CALLBACK DepartComTechWndProc(HWND hWnd,
				UINT Message, UINT wParam,LONG lParam)

{
RECT Rect;
static UINT nFlag=MF_ENABLED;

char* pContent[]=
{
"Enable exit",
"Disable exit"

};
static UINT nIndex=0;


//here error 2 was fixed
static HANDLE hBitmap;
int nDimension;

switch(Message)
{
case WM_CREATE:
	/*nDimension=GetSystemMetrics(SM_CYMENUCHECK);
	hBitmap=LoadImage(hInst,"my.bmp", IMAGE_BITMAP,
	nDimension,nDimension,LR_LOADFROMFILE);
	AppendMenu(GetMenu(hWnd),MFT_BITMAP,IDM_Bitmap, (char *) hBitmap);*/
	break;

case WM_COMMAND:
	switch(wParam)
	{
	case IDM_Enable_Disable:
		EnableMenuItem(hFileMenu, IDM_Exit, MF_BYCOMMAND|nFlag);
		nFlag=(nFlag==MF_ENABLED)? MF_GRAYED:MF_ENABLED;
		nIndex=(nIndex==0)?1:0;
		ModifyMenu(hFileMenu,IDM_Enable_Disable,
			MF_BYCOMMAND|MF_STRING,IDM_Enable_Disable,
			pContent[nIndex]);
		break;
//
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
		(LPARAM) pMessages[3+LOWORD(wParam)]);
	return 0;
	}
	if((UINT)HIWORD(wParam)& MFT_BITMAP)
	{
		MessageBox(hWnd, "You used our smile-menu!!", "Information", MB_OK | MB_ICONINFORMATION);
	return 0;
	}
	SendMessage(hStatusWindow,SB_SETTEXT,(WPARAM) 0,
		(LPARAM) pMessages[LOWORD(wParam)]);
	return 0;
case WM_DESTROY:
	DeleteObject(hBitmap);
	PostQuitMessage(0);
	return 0;
}
return DefWindowProc(hWnd,Message,wParam,lParam);
}

