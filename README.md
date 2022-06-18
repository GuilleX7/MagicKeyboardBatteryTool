# MagicKeyboardBatteryTool
Small tool for reading battery charge level from a Magic Keyboard using HIDAPI

## Important notes
Right now, it only works on GNU/Linux using hidraw backend and a keyboard connected via Bluetooth. Libusb backend will open the device, but will fail to get the battery charge level. Windows opens all HID keyboards and mouses for exclusive use, so it's unlikely you can get this to work unless you use a custom driver or something (if you do, tell me how you did). Not tested on macOS yet.

## Building

To build this program, you will need a C compiler and `libhidapi-dev` installed in your system. You can either get it from the apt repositories:

```
apt get update
apt get install libhidapi-dev
```

Or build and install it: https://github.com/libusb/hidapi

Then, build this program:

```
gcc main.c -o mkbatterytool -lhidapi-hidraw
```

And you are finished!
