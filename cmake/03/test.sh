#!/bin/bash

cmake -S ./src -B ./build

cmake --build ./build

for exe in build/test_*; do
  eval "./$exe" && echo "$exe returned 0!"
done
