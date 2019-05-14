#!/bin/bash
#date +%d%m%y_%H%M
make -f makefile all_ESD --eval=gui=1 --eval=log_mode=1 -j 8
make -f makefile all_ESD_2 --eval=gui=1 --eval=log_mode=1
