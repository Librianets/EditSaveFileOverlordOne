#project name = overlord game unpack and pack = OG_UPAP

idir = $(wc)include/
libdir = $(wc)lib/
srcdir = $(wc)win32/
buildir = $(wc)build/
temp = $(wc)temp/
save = $(wc)save/
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