GRADER
-------
Copy and paste into unzipped source directory, this encompasses most of what
follows in the remainder of the readme.
```
mkdir build
cd build
cmake .. -DLOGGING=OFF -DDEBUG=OFF -DCMAKE_BUILD_TYPE=RELEASE
make images
```

Output directories to be aware of:
- `build` anything built is in here
- `build/testdata` output from inputs in testdata
- `build/inputs` output from inputs in inputs
- `build/lib/drivers` executables reside in here (Refer to later parts of readme
on usage)


To build for a release:
-------------

```
mkdir build
cd build
# ideally logging should be left on, but if google logging is not installed it
# wont work
cmake .. -DLOGGING=OFF -DDEBUG=OFF -DCMAKE_BUILD_TYPE=RELEASE
make
```

Creating Images
------------

### To build images for all test input data
*Note (assuming you followed the above steps so far, this will be dumped into
`build/testdata` directory)*

```
make testdata
```

Likewise for the input data (output dir: `build/inputs`)
```
make inputs
```

To do it all in one shot (both testdata and images):
```
make images
```

To use the executable directly:

```
cd build
./lib/drivers/Simple <input_file> [ <output_file> ]
```

Misc
------

Although it should work just fine on Isengard, you may need to change versions
of g++
```
export CXX=/usr/bin/g++44
```

To use clang instead of gcc, export before running cmake:

```
export CXX=/usr/bin/clang++
```
