To build for a release:

```
mkdir build
cd build
cmake .. -DLOGGING=OFF -DDEBUG=OFF -DCMAKE_BUILD_TYPE=RELEASE
make
```

To build images for all input test data:

```
make test
```
