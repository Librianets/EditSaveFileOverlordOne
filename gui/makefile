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
res 		= $(wg)res/

I 			= -I$(include) -I$(res) -L$(lib)
l 			= -lres
opt 		= -mwindows -fno-exceptions -municode
#-municode
# -D_UNICODE -DUNICODE
lang 		=

######
punt =,
prob =
space = $(prob) $(prob)
######
includefile 	= $(notdir $(wildcard $(w32)*.cpp))
includeobject 	= $(patsubst %.cpp, %.o, $(includefile))
includeobject_2 = $(subst $(space),$(punt),$(strip $(includeobject)))

all_ESD: dir rm windres test strip
	@echo "project name -> overlord game editor save data -> OG_ESD"

test: $(includeobject)
	@echo "gcc .o -->> .exe"
	@$(CC) $(temp){$(includeobject_2)} -o $(bui_d)$(exe) $(I) $(l) $(opt)

$(includeobject):
	@echo "gcc .cpp -->> .o"
	@$(CC) $(lang) -c $(w32)$*.cpp -o $(temp)$*.o $(I) $(l) $(opt)

ar:
	@echo "ar"

ranlib:
	@echo "ranlib"

windres:
	@echo "rc --> libres.a"
	@$(wres) --input=$(res)res.rc --output=$(lib)libres.a

strip:
	@echo "strip exe"
	@$(strip) $(bui_d)$(exe)

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
	@rm -f $(lib)*.a