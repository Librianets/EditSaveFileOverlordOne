#project name = overlord game editor save data = OG_ESD

##### functions ###############

define fn_GetStatusFile
$(shell function GetStatus(){ \
if ( test -f $2 ); \
then { if ( test $1 -nt $2 ); then echo fn_false; else echo notrebuild; fi; } \
else echo fn_false; fi; }; GetStatus $1 $2; );
endef
### fn_GetStatusFile проверяет существует ли $2, если да, то проверяет модификацию файла $1 относительно $2

##### dir #####
w32 		= $(d_gui)w32/
w64 		= $(d_gui)w64/
temp 		= $(d_gui)temp/
log 		= $(d_gui)log/
lib 		= $(d_gui)lib/
libcore 	= $(d_gui)libcore/
include 	= $(d_gui)include/
res 		= $(d_gui)res/
module 		= $(d_gui)module/
build 		= $(d_gui)build/
bui_r 		= $(build)release/
bui_d 		= $(build)debug/
###################################

projectopt	= -DWINAPIMSG -DINFOMODE -DINFOCONSOLE
debug 		=
resource 	= libres.a
prefixdebug = debug

ifdef debugmode
debug 		+= -g -ggdb
projectopt 	+= -DDEBUGMODE -DDEBUGLOG -DDEBUGCONSOLE -DINFOLOG
moduleOne 	= libcore04_$(prefixdebug).a
exe 		= og_esd_$(prefixdebug).exe
stripexe	= og_esd_$(prefixdebug)_strip.exe
else
moduleOne 	= libcore04.a
exe 		= og_esd.exe
stripexe	= og_esd_strip.exe
endif

library		= -l:libz.a -lstdc++ -lcomctl32 -lkernel32 -lcomdlg32 -luser32 -lgdi32 -l:libwinpthread.a 
projectlib 	= -l:$(moduleOne) -l:$(resource)
win32opt	= -mwindows -municode 
lang 		= -x c++

I 			= -I$(include) -I$(res) -I$(libcore) -I$(module)
L 			= $(projectlib) $(library) -L$(lib) -L$(libcore) -L$(module)

opt 		= $(debug) -fno-exceptions -static -static-libgcc -static-libstdc++ $(projectopt) $(win32opt)

######
punt =,
prob =
space = $(prob) $(prob)
######
ifdef debugmode
win32cpp 		= $(strip $(notdir $(wildcard $(w32)*.cpp)))
win32obj 		= $(strip $(patsubst %.cpp, %_$(prefixdebug).o, $(win32cpp)))
win32objsub		= $(strip $(subst $(space),$(punt),$(strip $(win32obj))))
modulecpp 		= $(strip $(notdir $(wildcard $(module)*.cpp)))
moduleobj 		= $(strip $(patsubst %.cpp, %_$(prefixdebug).o, $(modulecpp)))
moduleobjsub	= $(strip $(subst $(space),$(punt),$(strip $(moduleobj))))
else
win32cpp 		= $(strip $(notdir $(wildcard $(w32)*.cpp)))
win32obj 		= $(strip $(patsubst %.cpp, %.o, $(win32cpp)))
win32objsub		= $(strip $(subst $(space),$(punt),$(strip $(win32obj))))
modulecpp 		= $(strip $(notdir $(wildcard $(module)*.cpp)))
moduleobj 		= $(strip $(patsubst %.cpp, %.o, $(modulecpp)))
moduleobjsub	= $(strip $(subst $(space),$(punt),$(strip $(moduleobj))))
endif
####################################################################################################
debug:
	@echo "debug start"
	@echo "$(win32cpp)"
	@echo "$(win32obj)"
	@echo "$(win32objsub)"
	@echo "$(modulecpp)"
	@echo "$(moduleobj)"
	@echo "$(moduleobjsub)"
	@echo "$(CC)"
	@echo "debug end"

dir:
	@mkdir -v -p $(w32)
	@mkdir -v -p $(w64)
	@mkdir -v -p $(temp)
	@mkdir -v -p $(log)
	@mkdir -v -p $(lib)
	@mkdir -v -p $(libcore)
	@mkdir -v -p $(include)
	@mkdir -v -p $(res)
	@mkdir -v -p $(module)
	@mkdir -v -p $(build)
	@mkdir -v -p $(bui_r)
	@mkdir -v -p $(bui_d)
	
clearapp:
	@rm -f $(bui_d)*.log
	@rm -f $(bui_r)*.log
	@rm -f $(temp)$(stripexe)
	@rm -f $(temp)$(exe)

clearbuild:
	@rm -f $(bui_d)*.*
	@rm -f $(bui_r)*.*

clearres:
	@rm -f $(temp)$(resource)
	@rm -f $(libcore)$(resource)
	
clearmodule:
	@rm -f $(temp)$(moduleOne)
	@rm -f $(libcore)$(moduleOne)

deltemp:
	@rm -f $(temp)*.*

clean: deltemp clearmodule clearres clearbuild clearapp
	@echo -e ""

######
all_OGESD: module app
	@echo "build end"

all_OGESD_fast_1: $(moduleobj) $(win32obj) windres 
	@echo "fast_1 end"

all_OGESD_fast_2: moduleranlib cpmodulelib clearapp appbuild
	@echo "fast_2 end"
##
module: echomodule $(moduleobj) moduleranlib cpmodulelib
	@echo "module end"

echomodule:
	@echo "module start"

$(moduleobj):
	$(if $(strip $(findstring notrebuild,$(call fn_GetStatusFile,\
	$(module)$(strip $(patsubst %_$(prefixdebug), %, $*)).cpp,$(temp)$*.o))),\
	@echo -e "${GREEN} not rebuild module $* $(ECHO_DEF)",\
	@echo -e "${YELLOW} rebuild module $* $(ECHO_DEF)";\
	$(CC) $(lang) -c $(module)$(strip $(patsubst %_$(prefixdebug), %, $*)).cpp -o $(temp)$*.o $(I) $(opt))

moduleranlib: modulear
	@$(ranlib) $(temp)$(moduleOne)

modulear: clearmodule
	@$(ar) cr $(temp)$(moduleOne) $(temp){$(moduleobjsub)}

cpmodulelib:
	@cp $(temp)$(moduleOne) $(libcore)$(moduleOne)

##
app: echoapp clearapp $(win32obj) windres appbuild
	@echo "app end"

echoapp:
	@echo "app start"

$(win32obj):
	$(if $(strip $(findstring notrebuild,$(call fn_GetStatusFile,\
	$(w32)$(strip $(patsubst %_$(prefixdebug), %, $*)).cpp,$(temp)$*.o))),\
	@echo -e "${GREEN} not rebuild $* $(ECHO_DEF)",\
	@echo -e "${YELLOW} rebuild $* $(ECHO_DEF)";\
	$(CC) $(lang) -c $(w32)$(strip $(patsubst %_$(prefixdebug), %, $*)).cpp -o $(temp)$*.o $(I) $(opt))

windres: clearres
	@$(wres) --input=$(res)$(strip $(notdir $(wildcard $(res)*.rc))) --output=$(libcore)$(resource) $(I)

appbuild:
	$(CC) $(temp){$(win32objsub)} -o $(temp)$(exe) $(I) $(L) $(opt)
	@cp $(temp)$(exe) $(temp)$(stripexe)
	@$(strip) $(temp)$(stripexe)
ifdef debugmode
	@rm -f $(bui_d)$(exe)
	@rm -f $(bui_d)$(stripexe)
	@cp $(temp)$(exe) $(bui_d)$(exe)
	@cp $(temp)$(stripexe) $(bui_d)$(stripexe)
else
	@rm -f $(bui_r)$(exe)
	@rm -f $(bui_r)$(stripexe)
	@cp $(temp)$(exe) $(bui_r)$(exe)
	@cp $(temp)$(stripexe) $(bui_r)$(stripexe)
endif	