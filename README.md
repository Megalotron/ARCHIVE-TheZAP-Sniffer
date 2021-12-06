# TheZAP
Megalotron's sniffer and data injector

## Build

In order to build, you will need [cmake](https://cmake.org/download/).

It is recommended to create **2 separated build folders**.  
- One for the `binary`  
- One for the `unit tests`  

If you do not create a folder for each one, you will need to clean the folder if you wish to build the binary after building the unit tests.

### Binary

```shell
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

### Unit Tests

```shell
mkdir build-tests
cd build-tests
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON
cmake --build .
```