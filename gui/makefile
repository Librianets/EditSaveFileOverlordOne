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
libcore 	= $(wg)libcore/

I 			= -I$(include) -I$(res) -I$(libcore)
l 			= -lres -lpacker -lz -lstdc++ -lwinpthread -lcomdlg32 -luser32 -lgdi32 -L$(lib) -L$(libcore) 
# -lkernel32  -lcomdlg32
opt 		= -DWINAPIPROJECT -DLOGGING -mwindows -fno-exceptions -municode
optlib 		= -municode
# -static-libgcc -static-libstdc++ -DWIN32PROJECT -DDEBUG ComCtl32.dll
debug 		= -g -ggdb -DDEBUG
#-municode
# -D_UNICODE -DUNICODE
lang 		= -x c++

packname = packunpack
packlibname = libpacker.a


######
punt =,
prob =
space = $(prob) $(prob)
######
includefile 	= $(notdir $(wildcard $(w32)*.cpp))
includeobject 	= $(patsubst %.cpp, %.o, $(includefile))
includeobject_2 = $(subst $(space),$(punt),$(strip $(includeobject)))

ifdef log_mode
opt += -Dlog_mode
endif

all_ESD: start dir rm $(includeobject) 
#all_ESD_2: exe strip deltemp end
all_ESD_2: exe strip deltemp end

rebuildlib: libdel windres packlib
	@echo -e "rebuildlib"
	@rm -f $(libcore)*.o
	
libdel:
	@rm -f $(libcore)*.a
	@rm -f $(libcore)*.o

end:
	@echo -e ""
	@echo -e "${GREEN}Ending compile project."
	@echo -e "${YELLOW}Project name -> overlord game editor save data -> OG_ESD$(ECHO_C)"

start:
	@echo -e "${YELLOW}Start compile project."
	@echo -e "${GREEN}Project name -> overlord game editor save data -> OG_ESD"
	@echo -e "$(ECHO_C)"

exe:
	@echo -e "$(includeobject_2) -->> $(exe)"
	@$(CC) $(temp){$(includeobject_2)} -o $(bui_d)$(exe) $(I) $(l) $(opt) $(debug)

$(includeobject):
	@echo -e "$*.cpp -->> $*.o"
	@$(CC) $(lang) -c $(w32)$*.cpp -o $(temp)$*.o $(I) $(opt) $(debug)

packlib:
	@echo -e "$*.cpp -->> $*.o"
	@$(CC) $(lang) -c $(libcore)$(packname).cpp -o $(libcore)$(packname).o $(I) $(opt)
	@echo -e "ar packlib"
	$(ar) cr $(libcore)$(packlibname) $(libcore)$(packname).o
	@echo -e "ranlib packlib"
	$(ranlib) $(libcore)$(packlibname)

windres:
	@echo -e "res.rc --> libres.a"
	@$(wres) --input=$(res)res.rc --output=$(libcore)libres.a $(I)

strip:
	@echo -e "${YELLOW}strip $(exe)$(ECHO_C)"
	cp $(bui_d)$(exe) $(bui_r)$(exe)
	@$(strip) $(bui_r)$(exe)

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

clean: rm
	@echo -e ""