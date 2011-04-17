
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
LIBRARIES= -lwinspool -lcomctl32
SOURCES= *.cpp
HEADERS= *.hpp
OBJECTS= *.o
EXECUTABLE=x.exe

DEBUG= -g -O0

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBRARIES) $(DEBUG)

%.o: %.cpp %.hpp
	$(CC) $(CFLAGS) $< -o $@ $(DEBUG)


