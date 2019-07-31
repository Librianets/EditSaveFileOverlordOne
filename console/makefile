#project name = overlord game unpack and pack = OG_UPAP

######### dir ########
incl = $(d_cnsle)include/
lib = $(d_cnsle)lib/
libcore = $(d_cnsle)libcore/
w32 = $(d_cnsle)win32/
build = $(d_cnsle)build/
temp = $(d_cnsle)temp/
########################
exe = og_upap.exe 
L = -lz -L$(lib)
I = -I$(incl) -I./
D =
opt =
lang = -x c++
######
punt =,
prob =
space = $(prob) $(prob)
######
includefilecpp 	= $(strip $(notdir $(wildcard $(w32)*.c)))
includeobject 	= $(strip $(patsubst %.c, %.o, $(includefilecpp)))
includeobject_2 = $(strip $(subst $(space),$(punt),$(strip $(includeobject))))

###############################
##### functions ###############
define fn_GetStatusFile
$(shell function GetStatus(){ \
if ( test -f $2 ); \
then { if ( test $1 -nt $2 ); then echo fn_false; else echo notrebuild; fi; } \
else echo fn_false; fi; }; GetStatus $1 $2; );
endef
### fn_GetStatusFile проверяет существует ли $2, если да, то проверяет модификацию файла $1 относительно $2

###################################

debug:
	@echo "debug start"
	@echo "$(includefilecpp)"
	@echo "$(includeobject)"
	@echo "$(includeobject_2)"
	@echo "$(CC)"
	@echo "debug end"

all_OGUPAP: dir $(includeobject) exe strip
	@echo "build end"

exe: clear
	@echo "gcc .o -->> .exe"
	@$(CC) $(temp){$(includeobject_2)} $(L) -o $(build)$(exe)

$(includeobject):
	$(if $(strip $(findstring notrebuild,$(call fn_GetStatusFile,$(w32)$*.c,$(temp)$*.o))),\
	@echo -e "${GREEN} not rebuild $* $(ECHO_DEF)",\
	@echo -e "${YELLOW} rebuild $* $(ECHO_DEF)";\
	$(CC) $(lang) -c $(w32)$*.c -o $(temp)$*.o $(I) $(opt))

strip:
	@echo -e "${YELLOW} strip $(exe) $(ECHO_DEF)"
	@strip $(build)$(exe)

dir:
	@mkdir -v -p $(incl)
	@mkdir -v -p $(lib)
	@mkdir -v -p $(libcore)
	@mkdir -v -p $(w32)
	@mkdir -v -p $(build)
	@mkdir -v -p $(temp)

clear:
	@rm -f $(build)*.*

deltemp:
	@rm -f $(temp)*.*

clean: clear deltemp
	@echo -e "clean build"