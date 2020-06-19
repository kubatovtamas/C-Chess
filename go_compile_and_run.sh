rm -rf build
cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Release
make -C build
./build/src/main