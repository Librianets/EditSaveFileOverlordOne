#project name = overlord game unpack and pack = OG_UPAP

idir = ./console/include/
libdir = ./console/lib/
srcdir = ./console/win32/
buildir = ./console/build/
temp = ./console/temp/
save = ./console/save/
exe = OG_UPAP.exe 

l = $(libdir)libz.a
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