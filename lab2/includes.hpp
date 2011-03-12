#ifndef __includes_hpp
#define __includes_hpp

/*					*
 *	Refactored by Fedorov Alex	*
 *	   header: includes.hpp		*
 *					*/

// this windows version is needed for printer
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0500

#include <windows.h>
#include <winspool.h>
#include <cstring>
#include <cstdio>

#define just_param(x) x
#define just_comment just_param()
#define singleton just_comment

#endif
