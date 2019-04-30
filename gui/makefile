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

######
punt =,
prob =
space = $(prob) $(prob)
######
includefile 	= $(notdir $(wildcard $(w32)*.cpp))
includeobject 	= $(patsubst %.cpp, %.o, $(includefile))
includeobject_2 = $(subst $(space),$(punt),$(strip $(includeobject)))

all_ESD: dir rm test strip
	@echo "project name -> overlord game editor save data -> OG_ESD"

test: $(includeobject)
	@echo "gcc .o -->> .exe"
	@$(CC) $(temp)$(includeobject_2) -o $(bui_d)$(exe) $(I) $(l) $(opt)

$(includeobject):
	@echo "gcc .cpp -->> .o"
	@$(CC) $(lang) -c $(w32)$*.cpp -o $(temp)$*.o $(I) $(l) $(opt)

strip:
	@echo "strip exe"
	@strip $(bui_d)$(exe)

dir:
	@mkdir -v -p $(w32)
	@mkdir -v -p $(w64)
	@mkdir -v -p $(temp)
	@mkdir -v -p $(log)
	@mkdir -v -p $(lib)
	@mkdir -v -p $(include)
	@mkdir -v -p $(build)
	@mkdir -v -p $(bui_r)
	@mkdir -v -p $(bui_d)
	
rm:
	@rm -f $(bui_d)*.*
	@rm -f $(bui_r)*.*
	@rm -f $(temp)*.*