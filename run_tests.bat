g++ tests.cpp -o test_file.exe -std=c++14 lib/libraylib.a -I gtest/googletest/include/ -I gtest/googlemock/include/ -L libtest/ -lgtest_main -lgtest -lgmock_main -lgmock
test_file.exe