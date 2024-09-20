rm -rf CMakeFiles/
rm -rf CMakeCache.txt
cmake .
cmake --build . -v
./main
