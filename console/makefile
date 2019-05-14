#project name = overlord game unpack and pack = OG_UPAP

compile = i686-w64-mingw32
CC = $(compile)-gcc
ar = $(compile)-ar
ranlib = $(compile)-ranlib
wres = $(compile)-windres
strip = $(compile)-strip.exe

idir = ./include/
libdir = ./lib/
srcdir = ./win32/
buildir = ./build/
temp = ./temp/
save = ./save/
exe = OG_UPAP.exe 

l = -lz -L$(libdir)
I = -I$(idir) -I./
D =

all_UPAP: rm obj
	@echo "gcc .o -->> .exe"
	@$(CC) $(temp)funcsmain.o $(temp)main.o $(temp)overlord.o $(l) \
	-o $(buildir)$(exe) 
	@strip $(buildir)$(exe)

rm:
	@echo delete file
	@rm -f $(temp)*.o
	@rm -f $(buildir)*.exe
	@rm -f *.txt

obj:
	@echo "gcc .c -->> .o"
	@$(CC) -c $(srcdir)main.c -o $(temp)main.o $(I) $(D)
	@$(CC) -c $(srcdir)funcsmain.c -o $(temp)funcsmain.o $(I) $(D)
	@$(CC) -c $(srcdir)overlord.c -o $(temp)overlord.o $(I) $(D)