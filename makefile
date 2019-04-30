#project name = overlord game editor save data = OG_ESD
#project name = overlord game unpack and pack = OG_UPAP

CC = i686-w64-mingw32-gcc
ar = 
ranlib = 

wg = ./gui/
wc = ./console/

include console/makefile
include gui/makefile

BLACK='\033[0;30m'     #  ${BLACK}    # чёрный цвет знаков
RED='\033[0;31m'       #  ${RED}      # красный цвет знаков
GREEN='\033[0;32m'     #  ${GREEN}    # зелёный цвет знаков
YELLOW='\033[0;33m'     #  ${YELLOW}    # желтый цвет знаков
BLUE='\033[0;34m'       #  ${BLUE}      # синий цвет знаков
MAGENTA='\033[0;35m'     #  ${MAGENTA}    # фиолетовый цвет знаков
CYAN='\033[0;36m'       #  ${CYAN}      # цвет морской волны знаков
GRAY='\033[0;37m'       #  ${GRAY}      # серый цвет знаков
ECHO_C='\033[0m'		# все атрибуты по умолчанию




#all: all_UPAP all_ESD

all:
	@echo all_UPAP all_ESD
