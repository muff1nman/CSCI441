To build:
-----------
mkdir build
cd build
cmake ..
make


To run:
----------
cd build
./lib/glviewer [input-file]

*note* if arguments are not supplied for the input file, it will attempt to open
a file named "input.t" in the *current working directory* so you will have to
copy an input file into the build directory if you wish to use the default file
name.

Or using the makefile:
---------
make
./glviewer [input-file]
