// author Fedorov Alex

#include "api7.hpp"

#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include "buttons.h"

HINSTANCE hInst;
HWND hWnd; 
int nRadioButtonId;

UINT uCheckBoxesState[3]={MF_UNCHECKED,
							MF_UNCHECKED,
							MF_UNCHECKED};

long WINAPI ButtonsExampleWndProc(HWND,UINT,UINT,LONG);
BOOL CALLBACK ButtonsExampleDialogProc(HWND,UINT,WPARAM,LPARAM);
BOOL CALLBACK ShopDialogDialogProc(HWND hDlg,
			UINT Message,WPARAM wParam,
					   LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, 
					HINSTANCE hPrevInstance,
				LPSTR lpszCmdParam, int nCmdShow)
{


WNDCLASS WndClass; 
MSG Msg;
char szClassName[]="ButtonsExample";
hInst=hInstance;

WndClass.style=CS_HREDRAW|CS_VREDRAW;
WndClass.lpfnWndProc=ButtonsExampleWndProc;
WndClass.cbClsExtra=0;
WndClass.cbWndExtra=0;
WndClass.hInstance=hInstance;
WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
WndClass.hbrBackground=(HBRUSH) GetStockObject(WHITE_BRUSH);
WndClass.lpszMenuName="ButtonsExampleMenu";
WndClass.lpszClassName= szClassName;

if(!RegisterClass(&WndClass))
{
	MessageBox(NULL,"Cannot register class","Error",MB_OK);
	return 0;
}

hWnd=CreateWindow(szClassName,"Seventh Example",
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
//отобразить окно		   
ShowWindow(hWnd,nCmdShow);
UpdateWindow(hWnd);

while(GetMessage(&Msg,NULL,0,0))
{
	TranslateMessage(&Msg);
	DispatchMessage(&Msg);

}
return Msg.wParam;
}

long WINAPI ButtonsExampleWndProc(HWND hWnd,
				UINT Message, UINT wParam,LONG lParam)

{
static BOOL bFlag=FALSE;
static HMENU hMenu1,hMenu2;
int i;

switch(Message)
{
case WM_CREATE:
	hMenu1=GetSubMenu(GetSubMenu(GetMenu(hWnd),1),0);
	hMenu2=GetSubMenu(GetSubMenu(GetMenu(hWnd),1),1);
	CheckMenuRadioItem(hMenu1,IDM_RadioButton1,
								IDM_RadioButton2,
								IDM_RadioButton3,
								MF_BYCOMMAND);
	nRadioButtonId=IDM_RadioButton1+102;
	for(i=0;i<3;i++)
	CheckMenuItem(hMenu2,IDM_CheckButton1+i,
	MF_UNCHECKED);
	break;

case WM_COMMAND:
	printf("%d\n", LOWORD(wParam));
	switch(LOWORD(wParam))
	{
	case IDM_EXIT:
		SendMessage(hWnd,WM_CLOSE,NULL,NULL);
	break;
	case IDM_RadioButton1:
	case IDM_RadioButton2:
	case IDM_RadioButton3:
		nRadioButtonId=LOWORD(wParam)+102;
	CheckMenuRadioItem(hMenu1,IDM_RadioButton1,
//								IDM_RadioButton2,
								IDM_RadioButton3,
								LOWORD(wParam),
								MF_BYCOMMAND);
	break;
	case IDM_CheckButton1:
	case IDM_CheckButton2:
	case IDM_CheckButton3:
	i=LOWORD(wParam)-105;
uCheckBoxesState[i]=uCheckBoxesState[i]==MF_CHECKED?
										MF_UNCHECKED:
										MF_CHECKED;
	CheckMenuItem(hMenu2,LOWORD(wParam),MF_BYCOMMAND|
							uCheckBoxesState[i]);			
	break;	
	case IDM_DisplayDialog:
		DialogBox(hInst,"ButtonsExample",
			hWnd,ButtonsExampleDialogProc);
		break;
	case IDM_DisplayDialog2:
		DialogBox(hInst,"ShopDialog",
			hWnd,ShopDialogDialogProc);
		break;
	}
	break;


case WM_DESTROY:

	PostQuitMessage(0);
	return 0;
}
return DefWindowProc(hWnd,Message,wParam,lParam);
}

BOOL CALLBACK ButtonsExampleDialogProc(HWND hDlg,
			UINT Message,WPARAM wParam,
					   LPARAM lParam)
{
	int i;
	char cMyMessage[80];

	switch(Message)
	{
	case WM_INITDIALOG:
	SendDlgItemMessage(hDlg,nRadioButtonId,BM_SETCHECK,
						BST_CHECKED,0);
	for(i=IDC_CHECKBOX1;i<=IDC_CHECKBOX3;i++)
		if(uCheckBoxesState[i-208])
			SendDlgItemMessage(hDlg,i,BM_SETCHECK,
			BST_CHECKED,0);
		return TRUE;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{

		case IDC_RADIOBUTTON1:
		case IDC_RADIOBUTTON2:
		case IDC_RADIOBUTTON3:
sprintf(cMyMessage,"Message from RadioButton%d",
		LOWORD(wParam)-203);
SendDlgItemMessage(hDlg,IDC_STATUSBAR,SB_SETTEXT,
				   (WPARAM)0,(LPARAM)cMyMessage);
CheckMenuRadioItem(GetSubMenu
				   (GetSubMenu(GetMenu(hWnd),1),0),
				   IDM_RadioButton1,IDM_RadioButton3,
					LOWORD(wParam)-102,MF_BYCOMMAND);
return FALSE;

		case IDC_CHECKBOX1:
		case IDC_CHECKBOX2:
		case IDC_CHECKBOX3:
sprintf(cMyMessage,"Message from CheckBox%d",
		LOWORD(wParam)-207);
SendDlgItemMessage(hDlg,IDC_STATUSBAR,SB_SETTEXT,
				   (WPARAM)0,(LPARAM)cMyMessage);
i=LOWORD(wParam)-208;
uCheckBoxesState[i]=uCheckBoxesState[i]==MF_CHECKED?
					MF_UNCHECKED:
					MF_CHECKED;

CheckMenuItem(GetSubMenu
		   (GetSubMenu(GetMenu(hWnd),1),1),
			LOWORD(wParam)-103,
			uCheckBoxesState[i]);
return FALSE;
		case IDC_BUTTON1:
SendDlgItemMessage(hDlg,IDC_STATUSBAR,SB_SETTEXT,
				   (WPARAM)0,
				   (LPARAM)"Message from PushButton");
return TRUE;
		case IDC_BUTTON2:
		i=IDC_RADIOBUTTON1;
		while(!SendDlgItemMessage(hDlg,i,
			BM_GETCHECK,0,0)) i++;
		nRadioButtonId=i;
for(i=IDC_CHECKBOX1;i<=IDC_CHECKBOX3;i++)
	uCheckBoxesState[i-208]=SendDlgItemMessage(hDlg,i,
	BM_GETCHECK,0,0)==0?
	MF_UNCHECKED: MF_CHECKED;
EndDialog(hDlg,0);
return TRUE;
		}
		break;
	}
	return FALSE;
}

BOOL CALLBACK ShopDialogDialogProc(HWND hDlg,
			UINT Message,WPARAM wParam,
					   LPARAM lParam){

	//printf("here\n");

	switch(Message)
	{
	case WM_INITDIALOG: break;
	case WM_COMMAND: break;
	}
	return TRUE;

}


		

