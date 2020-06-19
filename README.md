######## C_Chess #########

Compiling
compile_release.sh
```shell script
cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Release
make -C build
```

Debugging
debug.sh
```shell script
cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Release
make -C build
```

Run
run.sh
```shell script
./build/src/main
```

Clean
clean.sh
```shell script
rm -rf build
```

All-in-one Clean-Compile-Run
go_compile_and_run.sh
```shell script
cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Release
make -C build
./build/src/main
```

Library unit test
test.sh
```shell script
./build/tst/utest-lib
```