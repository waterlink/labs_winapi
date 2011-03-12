
#				# 
#	by Fedorov Alex		#
# makefile for winapi projects	#
# compiling under linux, using	#
# 	    mingw32		#
#				#

# CC = g++ using mingw or cygnus on windows
CC=i586-mingw32msvc-gcc
CFLAGS=-c -Wall -mwindows
LDFLAGS= -mwindows -Wl,--allow-multiple-definition
SOURCES=x.cpp wininitcore.cpp winmsgcore.cpp imgcore.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=x.exe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

