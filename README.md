# cooloverlays

this is a template project for raylib to do stuff on the screen with no windows, but the screen!
it is like an overlay on a screen which dedects mouse inputs and stuff and draw on it with raylib

## How to install the dependencies to build

For Windows, run:
  ```pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-raylib```

For Fedora Based Distributions:
  
  ```sudo dnf install raylib-devel libX11-devel```

For Ubuntu/Debian;

  ```sudo apt install libraylib-dev libx11-dev```

## how to build

  1. cd to the project root directory
  2. run ```bash build.bash [os("linux" or "windows")]```
  3. when it has built, there will be a file named "overlay" or "overlay.exe" executables, or a different name depending on when you set in ```build.bash```.

# Important:

- You MUST run this as Administirator.
  - For Linux, Just ```sudo ./overlay``` or ```sudo ./[whatever you set the executable name in build.bash]```
  - For Windows, run the built executable with administirator bro its easy or whatever

  
    
