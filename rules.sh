#!/bin/bash
set -e

ME=`basename $0`
function print_help() 
{
    echo "Обработчик makefile"
    echo
    echo "Использование: $ME options..."
    echo "Параметры:"
    echo "  -g opt            Cборка gui версии (требуются дополнительные ключи)"
    echo "  -c                Cборка console версии"
    echo "  -h                Справка"
    echo "  Параметры gui:"
    echo "  l - сборка libcore"
    echo "  e - сборка проекта"
    echo "  a - сборка всего (без модулей)"
    echo "  m - модули"
    echo
}

function console_f() 
{
    make -f globalmake all_UPAP --eval=console=1
}

function gui_f()
{
if [[ $1 = "e" ]]
then
    make -f globalmake build_project_fast --eval=gui=1 -j 8
	make -f globalmake build_project --eval=gui=1
fi

if [[ $1 = "l" ]]
then
	make -f globalmake rebuildlib --eval=gui=1
fi

if [[ $1 = "a" ]]
then
	gui_f l
	gui_f e
fi

if [[ $1 = "m" ]]
then
	make -f globalmake module --eval=gui=1
fi

return 0
}

if [ $# = 0 ]; then
    print_help
fi

while getopts ":hcg:" opt
do
    case $opt in
        c) console_f;;
        g) gui_f $OPTARG;;
        h) print_help;;
        *) echo "Неправильный параметр";exit 1;;
    esac
done

exit 0