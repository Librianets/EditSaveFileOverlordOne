#!/bin/bash
set -e

CPU=4

ME=`basename $0`
function print_help() 
{
    echo "Обработчик makefile"
    echo
    echo "Использование: $ME options..."
    echo "Параметры:"
    echo "  -g opt            Cборка gui версии (требуются дополнительные ключи)"
    echo "  -c opt            Cборка console версии"
    echo "  -h                Справка"
    echo ""
    echo "  Параметры console:"
    echo "  all - сборка console"
    echo "  debug - вывод переменных"
    echo "  clean - очистка сборки"
    echo ""
    echo "  Параметры gui:"
    echo "  all - полная сборка"
    echo "  alls - тихая сборка"
    echo "  allfast - быстрая сборка (cpu=$CPU)с"
    echo "  buildrelease - сборка только релиза"
    echo "  builddebug - сборка только дебага"
	echo "  clean - очистка сборки"
    echo
}

#переработать и make и bash, а то все коряво...
#

function console_f() 
{
if [[ $1 = "all" ]]
then
    make -f globalmake all_OGUPAP --eval=make_console=1, host_win32=1
elif [[ $1 = "debug" ]]
then
	make -f globalmake debug --eval=make_console=1, host_win32=1
elif [[ $1 = "clean" ]]
then
	make -f globalmake clean --eval=make_console=1, host_win32=1
else
	echo "problems function console_f"
	return 255
fi
return 0
}

function gui_f()
{
if [[ $1 = "all" ]]
then
    make -f globalmake all_OGESD --eval=make_gui=1, host_win32=1
    make -f globalmake all_OGESD --eval=make_gui=1, host_win32=1, debugmode=1
elif [[ $1 = "alls" ]]
then
    make --silent --file=globalmake all_OGESD --eval=make_gui=1, host_win32=1
    make --silent --file=globalmake all_OGESD --eval=make_gui=1, host_win32=1, debugmode=1
elif [[ $1 = "allfast" ]]
then
    make --silent --file=globalmake all_OGESD_fast_1 --eval=make_gui=1, host_win32=1 -j $CPU
	make --silent --file=globalmake all_OGESD_fast_1 --eval=make_gui=1, host_win32=1, debugmode=1 -j $CPU
    make --silent --file=globalmake all_OGESD_fast_2 --eval=make_gui=1, host_win32=1
    make --silent --file=globalmake all_OGESD_fast_2 --eval=make_gui=1, host_win32=1, debugmode=1
elif [[ $1 = "debug" ]]
then
	make -f globalmake debug --eval=make_gui=1, host_win32=1
	make -f globalmake debug --eval=make_gui=1, host_win32=1, debugmode=1
elif [[ $1 = "buildrelease" ]]
then
	make -f globalmake all_OGESD --eval=make_gui=1, host_win32=1
elif [[ $1 = "builddebug" ]]
then
	make -f globalmake all_OGESD --eval=make_gui=1, host_win32=1, debugmode=1
elif [[ $1 = "clean" ]]
then
	make -f globalmake clean --eval=make_gui=1, host_win32=1
else
	echo "problems function gui_f"
	return 255
fi

return 0
}

if [ $# = 0 ]; then
    print_help
fi

while getopts ":hc:g:" opt
do
    case $opt in
        c) console_f $OPTARG;;
        g) gui_f $OPTARG;;
        h) print_help;;
        *) echo "Неправильный параметр";exit 1;;
    esac
done

exit 0