#include "includes.hpp"
#include "prototypes.hpp"
#include "constants.hpp"

HANDLE
img_load(
		HWND & hWnd,
		const char * path,
		int imgtype
	){

	static HANDLE
	hBitmap;

	static bool 
	loaded = false;

	if (!loaded){

		hBitmap = LoadImage(
					NULL,
					path, 
					imgtype,
					0,
					0,
					LR_LOADFROMFILE
				);

		loaded = true;

	}

	return hBitmap;

}

