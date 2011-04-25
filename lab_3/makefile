
#				# 
#	by Fedorov Alex		#
# makefile for winapi projects	#
# compiling under linux, using	#
# 	    mingw32		#
#				#

# CC = g++ using mingw or cygnus on windows
CC=i586-mingw32msvc-gcc
RC=i586-mingw32msvc-windres
CFLAGS=-c -Wall -mwindows
LDFLAGS= -mwindows -Wl,--allow-multiple-definition
LIBRARIES= -lwinspool -lcomctl32
SOURCES= *.cpp
HEADERS= *.hpp
RESOURCES= *.rc
OBJECTS= *.o #*.coff
EXECUTABLE=x.exe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBRARIES)

%.coff: %.rc
	$(RC) -i $< -o $@

%.o: %.cpp %.hpp
	$(CC) $(CFLAGS) $< -o $@



