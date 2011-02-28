CC=i586-mingw32msvc-gcc
CFLAGS=-c -Wall -mwindows
LDFLAGS=
SOURCES=x.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=x.exe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

