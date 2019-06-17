# Привести наконец в порядок... после либкоры 0.3


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

sys = /usr/i686-w64-mingw32/sys-root/mingw/

I 			= -I$(include) -I$(res) -I$(libcore) 
#-I$(sys)include/gtk-3.0/ \
#-I$(sys)include/glib-2.0/ -I$(sys)lib/glib-2.0/include/ -I$(sys)lib/ -I$(sys)include/ -I$(sys)include/pango-1.0/ \
#-I$(sys)include/cairo/ -I$(sys)include/gdk-pixbuf-2.0/ -I$(sys)include/atk-1.0/

l 			= $(projectlib) -lz -lstdc++ -lcomctl32 -lcomdlg32 -luser32 -lgdi32 -lgdiplus -lUxTheme $(sys)/lib/libwinpthread.a -L$(lib) -L$(libcore)
#-lgtk-3 -lgdk-3 \ -lwinpthread
# -L/usr/i686-w64-mingw32/sys-root/mingw/lib/
# -lkernel32  -lcomdlg32
opt 		= -fno-exceptions -static -static-libgcc -static-libstdc++ $(optproject) $(optwin32)
optwin32	= -mwindows -municode 
optproject	= -DDEBUGMODE -DLOGGING -DWINAPIMSG -DWINAPIPROJECT -DWINAPICONSOLE

projectlib 	= -l:libdebug.a -l:libpacker.a -l:libres.a
# -static-libgcc -static-libstdc++ -DWIN32PROJECT -DDEBUG ComCtl32.dll
debug 		= -g -ggdb
#-municode
# -D_UNICODE -DUNICODE
lang 		= -x c++

packname = packunpack
debugname = debug
packlibname = libpacker.a
debuglibname = libdebug.a


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

rebuildlib: libdel windres packlib debuglib
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

debuglib:
	@echo -e "$*.cpp -->> $*.o"
	@$(CC) $(lang) -c $(libcore)$(debugname).cpp -o $(libcore)$(debugname).o $(I) $(opt)
	@echo -e "ar debuglib"
	$(ar) cr $(libcore)$(debuglibname) $(libcore)$(debugname).o
	@echo -e "ranlib debuglib"
	$(ranlib) $(libcore)$(debuglibname)

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

module:
	i686-w64-mingw32-gcc $(wg)module/GTK.cpp -o $(wg)module/gtk.exe \
	-lz -lstdc++ -lcomctl32 -lcomdlg32 -luser32 \
	$(sys)lib/libwinpthread.a -L$(lib) -L$(libcore) \
	-mwindows -static \
	`PKG_CONFIG_LIBDIR=yes PKG_CONFIG_PATH=/usr/i686-w64-mingw32/sys-root/mingw/lib/pkgconfig/ pkg-config --cflags gio-2.0 gtk+-3.0 librsvg-2.0 --libs gio-2.0 gtk+-3.0 gmodule-2.0 librsvg-2.0 epoxy`

#	-I./../../src/gtk/ \
#	-I./../../src/glib/glib/ \
#	-I./../../src/glib/
#	-static-libgcc -static-libstdc++

#	-O3 -lm \
#	 \
#	-I/usr/i686-w64-mingw32/sys-root/mingw/ \
#	-I/usr/i686-w64-mingw32/sys-root/mingw/lib/ \
#	-I/usr/i686-w64-mingw32/sys-root/mingw/include/
	$(strip) $(wg)module/gtk.exe
#	-I/usr/i686-w64-mingw32/sys-root/mingw/include/gtk-3.0/ \
#	-I/usr/i686-w64-mingw32/sys-root/mingw/include/glib-2.0/ \
#	-I/usr/i686-w64-mingw32/sys-root/mingw/lib/glib-2.0/include/ \
#	r:\usr\i686-w64-mingw32\sys-root\mingw\lib\pkgconfig\

	