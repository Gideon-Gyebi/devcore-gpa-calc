GKGDev Core 5: Sprint Setup Check List
1. Install VS Code
	a. install extension (C/C++, Code Runner)

2. Install Git for windows
	a. Default editor -> Select: VS Code as default Git editor
	b. PATH environment -> Select: Git from the command line and also from 3rd-party software
	c. Line ending conversion -> Select: Checkout Windows-style, commit Unix-style line endings
	d. Terminal emulator -> Select: Use bundled OpenSSH
				Select: Use MinTTY (default terminal) → gives Git Bash

3. Install MSYS2 (Build Tools for C)
	a. open msys2 mingw64 terminal -> run 'pacman -Syu'
	b. close terminal when done and re-open -> run 'pacman -Syu' one more time to complete
	c. install dependences -> run
		i. 'pacman -S mingw-w64-x86_64-gtk4'
		ii. 'pacman -S mingw-w64-x86_64-gcc'
		iii. 'pacman -S mingw-w64-x86_64-pkg-config'

	d. or as one command -> pacman -S mingw-w64-x86_64-gtk4 mingw-w64-x86_64-gcc mingw-w64-x86_64-pkg-config

4. In VS Code
	a. open command palette -> ctrl + shift + p
	b. type -> 'C/C++: Edit configurations (UI)' and open it
	c. look for "Include path" -> paste paths
C:/msys64/mingw64/include/**
C:/msys64/mingw64/lib/*/include/**

5. Add MSYS2 MinGW64 terminal profile in VS Code
	a. open command palette -> ctrl + shift + p
	b. type -> 'Preferences: Open User Settings (JSON)' and open it

OR
File → Preferences → Settings → Terminal → Integrated → Profiles: Windows
	c. add the following:
"terminal.integrated.profiles.windows": {
    "MSYS2 MinGW64": {
        "path": "C:\\msys64\\msys2_shell.cmd",
        "args": ["-defterm", "-here", "-mingw64"]
    }
},
"terminal.integrated.defaultProfile.windows": "MSYS2 MinGW64"

OR

"Git Bash": {
            "path": "D:\\Program Files\\Git\\bin\\bash.exe",
            "args": [
                "--login",
                "-i"
            ]
        },
        "MSYS2 MinGW64": {
            "path": "C:\\msys64\\msys2_shell.cmd",
            "args": [
                "-defterm",
                "-here",
                "-mingw64"
            ]
        }

NOTE: If "terminal.integrated.profile.window" has already been added, then copy the terminal you want to add. Start from the terminal name (eg. "MSYS2 MinGW64") to end at curly bracket '}'.

6. Command to compile GTK4 GUI App
	a. gcc <source-code.c> -o <app-name> `pkg-config --cflags --libs gtk4`

7. Side note
TROUBLESHOOTING SECTION

added to path

C:\msys64\mingw64\bin
C:\msys64\usr\bin

environment variable

name : PKG_CONFIG_PATH
value : C:\msys64\mingw64\lib\pkgconfig

to get the dll files that need to go with the exe
when sharing to someone else (all in one folder)

ldd app.exe (or whatever your exe is called)