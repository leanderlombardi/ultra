# HORIMAKE

! .COMPILE:
	hcc -wco compout ./src/ultra.c ./src/download.c

% .INSTALL:
	inst -o /user/programs/ultra

% .INSTALL:
	inst -ru ultra

