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

I 			= -I$(include) -I$(res)
l 			= -lres -L$(lib) -static-libgcc -static-libstdc++
# -lkernel32 -luser32 -lgdi32 -lcomdlg32
opt 		= -mwindows -fno-exceptions -municode
#-municode
# -D_UNICODE -DUNICODE
lang 		= -x c++

######
punt =,
prob =
space = $(prob) $(prob)
######
includefile 	= $(notdir $(wildcard $(w32)*.cpp))
includeobject 	= $(patsubst %.cpp, %.o, $(includefile))
includeobject_2 = $(subst $(space),$(punt),$(strip $(includeobject)))

all_ESD: start dir rm windres test strip deltemp end
	

end:
	@echo -e ""
	@echo -e "${GREEN}Ending compile project."
	@echo -e "${YELLOW}Project name -> overlord game editor save data -> OG_ESD$(ECHO_C)"

start:
	@echo -e "${YELLOW}Start compile project."
	@echo -e "${GREEN}Project name -> overlord game editor save data -> OG_ESD"
	@echo -e "$(ECHO_C)"

test: $(includeobject)
	@echo -e "$(includeobject_2) -->> $(exe)"
	@$(CC) $(temp){$(includeobject_2)} -o $(bui_d)$(exe) $(I) $(l) $(opt)

$(includeobject):
	@echo -e "$*.cpp -->> $*.o"
	@$(CC) $(lang) -c $(w32)$*.cpp -o $(temp)$*.o $(I) $(l) $(opt)

ar:
	@echo -e "ar"

ranlib:
	@echo -e "ranlib"

windres:
	@echo -e "res.rc --> libres.a"
	@$(wres) --input=$(res)res.rc --output=$(lib)libres.a $(I)

strip:
	@echo -e "${YELLOW}strip $(exe)$(ECHO_C)"
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
	
rm: deltemp
	@rm -f $(bui_d)*.*
	@rm -f $(bui_r)*.*

deltemp:
	@rm -f $(temp)*.*
	@rm -f $(lib)*.a	