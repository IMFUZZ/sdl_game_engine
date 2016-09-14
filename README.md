
 ____  ____  _           ____    _    __  __ _____      _____ _   _  ____ ___ _   _ _____ 
/ ___||  _ \| |         / ___|  / \  |  \/  | ____|    | ____| \ | |/ ___|_ _| \ | | ____|
\___ \| | | | |   _____| |  _  / _ \ | |\/| |  _| _____|  _| |  \| | |  _ | ||  \| |  _|  
 ___) | |_| | |__|_____| |_| |/ ___ \| |  | | |__|_____| |___| |\  | |_| || || |\  | |___ 
|____/|____/|_____|     \____/_/   \_\_|  |_|_____|    |_____|_| \_|\____|___|_| \_|_____|

#WINDOWS : 

What you need : 

	- Windows 10 32Bit or 64Bit
	- A clone of the repository (obviously)
	- MinGW (with "make" and "G++")

Things to do :

	- Don't edit the Makefile (DON'T)
	- Add C:\MinGW\bin to your PATH (the environnement variable)
		- Than reboot.. (seems to be pretty important for MinGW)
	- Rename the "C:\MinGW\bin\mingw32-make.exe" executable for "C:\MinGW\bin\make.exe"
	- Make sure you can access "make" and "g++" using the Good ol' windows cmd (Using MinGW commandline may cause problems).

COMPILING! :

	- Open a windows cmd in the project root directory (where main.cpp is.. DUH!)
	- Type : 'make' (Without the ''.. DUHH)
	- The file "main.exe" should be created in the "./src" directory!

#LINUX :

What you need : 

	- Linux that can install SDL2 (Tested on SDL2)
	- A clone of the repository (obviously)
	- G++ (should already be included) and SDL2 (apt-get install libsdl2, pacman -S SDL2, etc depending on your system)

Things to do :

	- Don't edit the Makefile (DON'T)
	- Chill

COMPILING! :

	- Open a terminal in the project root directory
	- Type : 'make' (Without the ''.. DUHH)
	- The file ".main" should be created in the "./src" directory!
