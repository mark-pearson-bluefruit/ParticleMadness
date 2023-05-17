if not exist .\testbuild (
    mkdir testbuild
)
g++ test/tests.cpp src/render.c src/nextstep.c -o testbuild/test_file.exe -std=c++14 -I gtest/googletest/include/ -I src/include -L libtest/ -lgtest_main -lgtest
testbuild\test_file.exe