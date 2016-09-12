
 ____  ____  _           ____    _    __  __ _____      _____ _   _  ____ ___ _   _ _____ 
/ ___||  _ \| |         / ___|  / \  |  \/  | ____|    | ____| \ | |/ ___|_ _| \ | | ____|
\___ \| | | | |   _____| |  _  / _ \ | |\/| |  _| _____|  _| |  \| | |  _ | ||  \| |  _|  
 ___) | |_| | |__|_____| |_| |/ ___ \| |  | | |__|_____| |___| |\  | |_| || || |\  | |___ 
|____/|____/|_____|     \____/_/   \_\_|  |_|_____|    |_____|_| \_|\____|___|_| \_|_____|


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
	- Type : 'Make' (Without the ''.. DUHH)
	- The file "main.exe" should be created in the directory!