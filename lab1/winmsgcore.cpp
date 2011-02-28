
/*					*
 *	Refactored by Fedorov Alex	*
 *	  source: winmsgcore.cpp	*
 *					*/

#include "includes.hpp"
#include "prototypes.hpp"
#include "constants.hpp"

LRESULT CALLBACK 
WndProc(
			HWND hWnd,
			UINT Message, 
			UINT wParam,
			LONG lParam
		){	

	// we are interesting only in paint and destroy messages
	switch (Message){

		case WM_PAINT:

			on_paint(hWnd);

			return q_success;

		// somebody wants to close our window!
		case WM_DESTROY:

			// here we want to save smth, or clean up
			// but suddenly, project is too light, nothing to do here

			// tell system "everything is ok, close me"
			PostQuitMessage(q_success);

			return q_success;
	}

	// another message? don't care. call default window procedure
	return DefWindowProc(
				hWnd,
				Message,
				wParam,
				lParam
			);

}

void
mainloop(
		MSG & Msg
	){

	while(
			GetMessage(
					&Msg,
					NULL,
					msg_minfilter,
					msg_maxfilter
				)
		){

		// translating message to identic form
		TranslateMessage(&Msg);

		// force our window procedure to process our message
		DispatchMessage(&Msg);
	}

}

void
on_paint(
		HWND & hWnd
	){

	HDC 
	hDC; // device context handle

	PAINTSTRUCT 
	PaintStruct; // features of our painting area

	RECT 
	Rect; // painting area rectangle

	// get our device context handle
	hDC = BeginPaint(
				hWnd,
				&PaintStruct
			);

	// determine our client area for painting
	// usually, (0, 0), (a, b)
	// where a - width, b - height
	GetClientRect(
			hWnd,
			&Rect
		);

	// out our text in our format
	DrawText(
			hDC,
			td_text,
			td_nullterminated,
			&Rect,
			td_format
		);

	// finilization of painting
	EndPaint(
			hWnd,
			&PaintStruct
		);

}

