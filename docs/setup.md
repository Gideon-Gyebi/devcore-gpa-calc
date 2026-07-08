# GKGDev Core 5: Sprint Setup Check List

1. **Install VS Code**
	- install extension (C/C++, Code Runner)


2. Install Git for windows
	- Default editor -> Select: VS Code as default Git editor
	- PATH environment -> Select: Git from the command line and also from 3rd-party software
	- Line ending conversion -> Select: Checkout Windows-style, commit Unix-style line endings
	- Terminal emulator -> Select: Use bundled OpenSSH
				Select: Use MinTTY (default terminal) → gives Git Bash


3. Install MSYS2 (Build Tools for C)
	- open msys2 mingw64 terminal -> run `pacman -Syu`
	- close terminal when done and re-open -> run `pacman -Syu` one more time to complete
	- install dependences -> run
		
		`pacman -S mingw-w64-x86_64-gtk4`
		
		`pacman -S mingw-w64-x86_64-gcc`
		
		`pacman -S mingw-w64-x86_64-pkg-config`

	- or as one command -> `pacman -S mingw-w64-x86_64-gtk4 mingw-w64-x86_64-gcc mingw-w64-x86_64-pkg-config`


4. In VS Code
	- open command palette -> ctrl + shift + p
	- type -> 'C/C++: Edit configurations (UI)' and open it
	- look for "Include path" -> paste paths

		`C:/msys64/mingw64/include/**`

		`C:/msys64/mingw64/lib/*/include/**`


5. Add MSYS2 MinGW64 terminal profile in VS Code
	- open command palette -> ctrl + shift + p
	- type -> 'Preferences: Open User Settings (JSON)' and open it

			OR
			  File → Preferences → Settings → Terminal → Integrated → Profiles: Windows

	- add the following:
``` json
"terminal.integrated.profiles.windows": {
    "MSYS2 MinGW64": {
        "path": "C:\\msys64\\msys2_shell.cmd",
        "args": ["-defterm", "-here", "-mingw64"]
    }
},
"terminal.integrated.defaultProfile.windows": "MSYS2 MinGW64"
```

OR

```json
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
```

<span style="color:red;">NOTE:</span> If "terminal.integrated.profile.window" has already been added, then copy the terminal you want to add. Start from the terminal name (eg. "MSYS2 MinGW64") to end at curly bracket '}'.

6. Command to compile GTK4 GUI App
	- gcc <source-code.c> -o <app-name> `pkg-config --cflags --libs gtk4`

7. Side note
TROUBLESHOOTING SECTION

- added to path

`C:\msys64\mingw64\bin`

`C:\msys64\usr\bin`

environment variable

name : PKG_CONFIG_PATH
value : `C:\msys64\mingw64\lib\pkgconfig`

to get the dll files that need to go with the exe
when sharing to someone else (all in one folder)

ldd app.exe (or whatever your exe is called)