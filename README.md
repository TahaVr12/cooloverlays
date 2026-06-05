# cooloverlays

a template project for raylib that lets you draw on the screen itself with no window, just an overlay.

It stays on top of everything,it reads your global mouse position and clicks
and lets those clicks pass through to whatever is underneath while you draw on top with raylib

also im not sure if windows works for now

## Install the dependencies

**Windows**:

1. Install MSYS2
2. Run this in powershell: ``` C:\msys64\usr\bin\bash.exe -lc "pacman -S --needed mingw-w64-x86_64-gcc mingw-w64-x86_64-raylib" ```

**Fedora Based Distributions:**
```
sudo dnf install raylib-devel libX11-devel
```

**Ubuntu / Debian:**
```
sudo apt install libraylib-dev libx11-dev
```

## Build

1. `cd` into the project root
2. Run the build script, optionally passing the target OS:
```
   bash build.bash            # builds for the OS you're on
   bash build.bash linux      # force Linux
   bash build.bash windows    # force Windows
```
3. you will get an `overlay` (Linux) or `overlay.exe` (Windows) executable in the root or whatever you renamed `APP_NAME` to in `build.bash`.

## how do i run it bro

**Linux:** the overlay reads your mouse from `/dev/input`, which needs the `input` group.(this is a one-time setup btw):
```
sudo usermod -aG input $USER
```
then log out and back in. After that just run `./overlay` normally with no sudo needed. (`sudo ./overlay` works as a quick test, 
but running a GUI app as root can break on Wayland, so the group is the proper fix.)

**Windows:** just run `overlay.exe`. no need for admin.

## Notes

- Works on **X11 and Wayland** (including XWayland). The mouse is read via evdev,
  which sits below the display server, so it doesn't care which one you're on.
- On Wayland, mouse position is tracked from movement deltas, so it can drift from the real cursor over time,
  set a **no acceleration** pointer to fix it if you want it to perfectly on your cursor.
