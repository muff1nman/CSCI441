To build for a release:

```
mkdir build
cd build
# to turn off logging as well add -DLOGGING=OFF
cmake .. -DDEBUG=OFF -DCMAKE_BUILD_TYPE=RELEASE
make
```

To build images for all input test data:

```
make test
```

To use clang instead of gcc, export before running cmake:

```
export CXX=/usr/bin/clang++
```
