

### Environment

- cmake 3.0+
- gcc 6.3+

### Build the program

Open a terminal in the sample directory and execute the following command:

```
mkdir build
cd build
cmake ..
make -j$(nproc)
# or
# g++ -std=c++11 -Wall -g test01.cpp -o test01 
```

### Run  the program

Navigate to the build directory and launch the executable file to run the program:

```
./test01
```

### Result
