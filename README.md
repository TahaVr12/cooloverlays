
### Disclaimer: If you are on Linux, the Linux session must be X11, not Wayland!

# How to install the dependencies

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

  
    
