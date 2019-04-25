Compressed/uncompressed save data

Game: Overlord - Raising Hell

Version program: 0.1 (by Librianets)

Version game check: 0.4

progname.exe option -i input -o output 

-i name 	: name file input

-o name 	: name file output

-C 			: compressed

-D 			: uncompressed

-f 			: help

Sample: progname.exe -D -i SaveInfo.osi.tzf -o SaveInfo_uncompress.osi.tzf

Sample: progname.exe -C -i SaveInfo_uncompress.osi.tzf -o SaveInfo.osi.tzf



Implemented:
- compressed save data
- uncompressed save data

Awaiting implementation:
- editing in semi-automatic parameters of the passing game parameters (Items, upgrades, money, minions etc.)
- availability gui (win32)
