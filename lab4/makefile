all: main.exe
	cp main.exe /home/lexias/wine_d/cpp-nix/lab4/
	wine d:\\cpp-nix\\lab4\\main.exe
main.exe: main.o mainform.o mainform.coff explore.o __task.o
	i586-mingw32msvc-g++ __task.o main.o mainform.o mainform.coff explore.o -o main.exe -mwindows -lcomctl32
main.o: main.hpp main.cpp
	i586-mingw32msvc-g++ main.cpp -o main.o -mwindows -c
mainform.o: mainform.hpp mainform.cpp mainform.rc explore.rc
	i586-mingw32msvc-g++ mainform.cpp -o mainform.o -mwindows -c
	i586-mingw32msvc-windres -i mainform.rc -o mainform.coff
explore.o: explore.hpp explore.cpp
	i586-mingw32msvc-g++ explore.cpp -o explore.o -mwindows -c
__task.o: task __task.hpp
	echo "#include \"__task.hpp\"" > __task.cpp
	echo "char * __taskstring[] = {" >> __task.cpp
	cat task | sed 's/.*/\"&\",/g' >> __task.cpp
	echo "\"\"" >> __task.cpp
	echo "};" >> __task.cpp
	echo "char ** gettaskstring(){ return __taskstring; }" >> __task.cpp
	i586-mingw32msvc-g++ __task.cpp -o __task.o -mwindows -c

