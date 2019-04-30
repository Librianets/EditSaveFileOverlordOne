#project name = overlord game editor save data = OG_ESD
exe 		= OG_ESD.exe 

w32 		= $(wg)w32/
w64 		= $(wg)w64/
temp 		= $(wg)temp/
log 		= $(wg)log/
lib 		= $(wg)lib/
include 	= $(wg)include/
build 		= $(wg)build/
bui_r 		= $(build)release/
bui_d 		= $(build)debug/

I 			= -I $(include)
l 			= 
opt 		= -mwindows
lang 		=  -x c++ 

#gcc = x86_64-w64-mingw32-gcc

#include1 = winapi
#include2 = console
#include3 = global
#workdir = /cygdrive/w/learn/winapi
#tmp = $(workdir)/tmp
#include = $(workdir)/include
#f_include = -I$(workdir)/include
#f_o = -Dlia_windows -Dlia_linux $(f_include)
#f_exe = -mwindows



######
punt =,
prob =
space = $(prob) $(prob)
######
includefile 	= $(notdir $(wildcard $(w32)*.cpp))
includeobject 	= $(patsubst %.c, %.o, $(includefile))
includeobject_2 = $(subst $(space),$(punt),$(strip $(includeobject)))


#all: rm $(includeobject)
#	$(gcc) $(tmp)/{$(includeobject_2)} -o ./build/winapi.exe $(f_exe)

#$(includeobject):
#	$(gcc) -x c -c $(workdir)/win64/$*.c -o $(tmp)/$*.o $(f_o)




all_ESD:
	@echo "project name -> overlord game editor save data -> OG_ESD"

test:
	rm -f $(bui_d)*.exe
	rm -f $(bui_r)*.exe
	rm -f $(temp)*.o
	$(CC) $(lang) $(w32)$(includeobject) -o $(bui_d)$(exe) $(I) $(l) $(opt)
	strip $(bui_d)$(exe)
	@echo "project name -> overlord game editor save data -> OG_ESD"