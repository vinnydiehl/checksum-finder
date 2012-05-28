# Checksum Finder

Checksum Finder is an application to test file integrity by means of the MD5 hash algorithm. SHA-1 support is to be implemented soon.

## Usage

To test a file, simply press the Browse button (or Ctrl+O) and find the file that you wish to find the checksum of. The MD5 will automatically be calculated and displayed in the designated area- for large files (several hundred megabytes), give it a few seconds to process the file.

## Build Instructions

Checksum Finder is written in C++ using wxWidgets 2.8.12. The makefile for this program is configured for the default path that wxWidgets is installed to; if your builds are failing, your include directories may be different. If so, adjust the value of WXCFLAGS to the output of the following command:

    wx-config --cppflags

And set the value of WXLFLAGS to the output of:

    wx-config --libs

Run ```make``` to build the program, or ```make rebuild``` to completely rebuild the program and all object files.

```make clean``` will delete all object files while leaving the application intact, and ```make delete``` or ```make erase``` will completely delete all build artifacts, including the compiled application.
