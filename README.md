# Checksum Finder

Checksum Finder is an application to test file integrity by means of the MD5 hash algorithm. SHA-1 support is to be implemented soon.

## Usage

To test a file, simply press the Browse button (or Ctrl+O) and find the file that you wish to find the checksum of. The MD5 will automatically be calculated and displayed in the designated area- for large files (several hundred megabytes), give it a few seconds to process the file.

## Build Instructions

Running this will install all of the needed build tools for this application:

    sudo apt-get install build-essential libwxgtk2.8-dev

Checksum Finder is written in C++ using wxWidgets 2.8.12. If your compiler is having trouble finding the wxWidgets library and you know that you have it installed, check that there is output for the following commands:

    wx-config --cppflags
    wx-config --libs

Run ```make``` to build the program, or ```make rebuild``` to completely rebuild the program and all object files.

```make clean``` will delete all object files while leaving the application intact, and ```make delete``` or ```make erase``` will completely delete all build artifacts, including the compiled application.
