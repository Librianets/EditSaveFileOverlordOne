CC = i686-w64-mingw32-gcc
ar = 
ranlib = 
exe = OverlordG_esd.exe 
#project name = overlord game editor save data


idir = ./include/
libdir = ./lib/
srcdir = ./win32/
buildir = ./build/
temp = ./temp/
save = ./save/

l = $(libdir)libz.a
I = -I$(idir) -I./
D =

all: rm obj
	@echo "gcc .o -->> .exe"
	@$(CC) $(temp)funcsmain.o $(temp)main.o $(temp)overlord.o $(l) \
	-o $(buildir)$(exe) 
	@strip $(buildir)$(exe)

rm:
	@echo delete file
	@rm -f $(temp)*.*
	@rm -f $(buildir)*.*
	@rm -f *.txt

obj:
	@echo "gcc .c -->> .o"
	@$(CC) -c $(srcdir)main.c -o $(temp)main.o $(I) $(D)
	@$(CC) -c $(srcdir)funcsmain.c -o $(temp)funcsmain.o $(I) $(D)
	@$(CC) -c $(srcdir)overlord.c -o $(temp)overlord.o $(I) $(D)